-- circle_enemy.lua
local angle = 0
local ROTATION_SPEED = 4

function init()
  local tag = get_tag(this)
  local formation_index = tonumber(string.match(tag, "%d+"))
  local formation = scene.crosses[formation_index]

  -- Calcular un ángulo inicial basado en la posición inicial del enemigo
  local initial_x, initial_y = get_position(this)
  local dx = initial_x - formation.x
  local dy = initial_y - formation.y
  angle = math.atan2(dy, dx)
end

function update(dt)
  local tag = get_tag(this)
  local formation_index = tonumber(string.match(tag, "%d+"))
  local formation = scene.crosses[formation_index]

  local center_x = formation.x
  local center_y = formation.y
  local radius = formation.radius

  angle = angle + ROTATION_SPEED * dt

  local new_x = center_x + radius * math.cos(angle)
  local new_y = center_y + radius * math.sin(angle)

  local current_x, current_y = get_position(this)

  local vel_x = (new_x - current_x) / dt
  local vel_y = (new_y - current_y) / dt

  -- Establecer la nueva velocidad
  set_velocity(this, vel_x, vel_y)
end
