local center_x, center_y = 500, 500 -- Center of the circle
local radius = 100                  -- Radius of the circle
local speed = 2                     -- Rotation speed
local angle = 0                     -- Initial angle

function update()
  -- Update the angle
  angle = angle + speed * 0.01 -- Multiplying by 0.01 to make it smooth

  -- Calculate the new positions
  local new_x = center_x + radius * math.cos(angle)
  local new_y = center_y + radius * math.sin(angle)

  -- Get the current position
  local current_x, current_y = get_position(this)

  -- Calculate the velocity
  local vel_x = new_x - current_x
  local vel_y = new_y - current_y

  -- Set the new velocity
  set_velocity(this, vel_x, vel_y)
end
