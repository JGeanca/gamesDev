local angle = 0
local ROTATION_SPEED = 4

function init()
  -- init the enemy with the formation position
  local tag = get_tag(this)
  local formation_index = tonumber(string.match(tag, "%d+"))
  local formation = scene.circles[formation_index]

  local initial_x, initial_y = get_position(this)
  local dx = initial_x - formation.x
  local dy = initial_y - formation.y
  angle = math.atan2(dy, dx)
end

function update(dt)
  local tag = get_tag(this)
  local formation_index = tonumber(string.match(tag, "%d+"))
  local formation = scene.circles[formation_index]

  local center_x = formation.x
  local center_y = formation.y
  local radius = formation.radius

  -- update the angle
  angle = angle + ROTATION_SPEED * dt

  -- get the current position
  local current_x, current_y = get_position(this)

  -- calculate the new position
  local new_x = center_x + radius * math.cos(angle)
  local new_y = center_y + radius * math.sin(angle)

  -- calculate the velocity based on the new position
  local vel_x = (new_x - current_x) / dt
  local vel_y = (new_y - current_y) / dt

  -- set the velocity
  set_velocity(this, vel_x, vel_y)
end
