-- cross_enemy.lua
local ROTATION_SPEED = 0.5 -- Reducido para pruebas, ajusta según sea necesario

function init()
  local tag = get_tag(this)
  local formation_index = tonumber(string.match(tag, "%d+"))
  local formation = scene.crosses[formation_index]

  if not formation then
    print("Error: Formation not found for index " .. formation_index)
    return
  end

  local center_x, center_y = formation.x, formation.y
  local initial_x, initial_y = get_position(this)
  this.offset_x = initial_x - center_x
  this.offset_y = initial_y - center_y

  this.radius = math.sqrt(this.offset_x ^ 2 + this.offset_y ^ 2)
  this.initial_angle = math.atan(this.offset_y, this.offset_x)
  this.rotation_angle = 0

  print("Init: " ..
  tag ..
  ", Center: (" ..
  center_x .. ", " .. center_y .. "), Initial: (" .. initial_x .. ", " .. initial_y .. "), Radius: " .. this.radius)
end

function update(dt)
  local tag = get_tag(this)
  local formation_index = tonumber(string.match(tag, "%d+"))
  local formation = scene.crosses[formation_index]

  if not formation then
    print("Error: Formation not found in update for index " .. formation_index)
    return
  end

  this.rotation_angle = this.rotation_angle + ROTATION_SPEED * dt

  local new_x = formation.x + this.radius * math.cos(this.initial_angle + this.rotation_angle)
  local new_y = formation.y + this.radius * math.sin(this.initial_angle + this.rotation_angle)

  local current_x, current_y = get_position(this)

  if math.abs(new_x - current_x) > 0.01 or math.abs(new_y - current_y) > 0.01 then
    set_position(this, new_x, new_y)
    print("Update: " .. tag .. ", New Position: (" .. new_x .. ", " .. new_y .. "), Angle: " .. this.rotation_angle)
  end
end
