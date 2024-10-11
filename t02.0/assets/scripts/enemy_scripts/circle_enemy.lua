-- circle_enemy.lua
local speed = 1 -- Puedes ajustar esto para cambiar la velocidad de rotación
local angle = 0 -- Ángulo inicial

function update()
  local tag = get_tag(this)
  local formation_index = tonumber(string.match(tag, "%d+"))
  local formation = scene.crosses[formation_index]

  local center_x = formation.x
  local center_y = formation.y
  local radius = formation.radius

  angle = angle + speed * 0.01

  local initial_x, initial_y = get_position(this)
  local offset_x = initial_x - center_x
  local offset_y = initial_y - center_y

  local new_x = center_x + offset_x * math.cos(angle) - offset_y * math.sin(angle)
  local new_y = center_y + offset_x * math.sin(angle) + offset_y * math.cos(angle)

  local current_x, current_y = get_position(this)
  local vel_x = new_x - current_x
  local vel_y = new_y - current_y

  set_velocity(this, vel_x, vel_y)
end
