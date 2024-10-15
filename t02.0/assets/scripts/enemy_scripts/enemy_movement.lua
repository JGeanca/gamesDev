local initial_position = { x = 0, y = 0 }
local max_distance = 140
local direction = 1 -- 1 para moverse en la dirección positiva, -1 para la negativa

function init()
  initial_position.x, initial_position.y = get_position(this)
end

function update(dt)
  local current_x, current_y = get_position(this)
  local vel_x, vel_y = get_velocity(this)

  local is_horizontal = math.abs(vel_x) > math.abs(vel_y)
  local distance = is_horizontal and (current_x - initial_position.x) or (current_y - initial_position.y)
  local velocity = is_horizontal and vel_x or vel_y

  -- Calcula la posición después del movimiento
  local next_distance = distance + velocity * dt * direction

  -- Verifica si necesitamos cambiar de dirección o ajustar la posición
  if (direction == 1 and next_distance >= max_distance) or (direction == -1 and next_distance <= 0) then
    -- Calcula el exceso de movimiento
    local overflow = direction == 1 and (next_distance - max_distance) or -next_distance

    -- Cambia la dirección
    direction = -direction

    -- Ajusta la posición para que esté exactamente en el límite
    if is_horizontal then
      set_position(this, initial_position.x + (max_distance * (direction == -1 and 1 or 0)), current_y)
    else
      set_position(this, current_x, initial_position.y + (max_distance * (direction == -1 and 1 or 0)))
    end

    -- Ajusta la velocidad para el movimiento restante
    velocity = direction * math.abs(velocity)
    next_distance = direction * overflow
  end

  -- Aplica la velocidad ajustada
  if is_horizontal then
    set_velocity(this, velocity, 0)
  else
    set_velocity(this, 0, velocity)
  end
end
