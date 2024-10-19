function on_collision(other)
  local this_tag = get_tag(this)
  local other_tag = get_tag(other)
  local collision_type = get_collision_type(this, other)
  local this_x, this_y = get_position(this)

  if other_tag == "barrier" or other_tag == "invisible_barrier" then
    local vel_x, vel_y = get_velocity(this)

    local collision_actions = {
      top = function()
        set_position(this, this_x, this_y + 1)
        set_velocity(this, vel_x, -vel_y)
      end,
      bottom = function()
        set_position(this, this_x, this_y - 1)
        set_velocity(this, vel_x, -vel_y)
      end,
      left = function()
        set_position(this, this_x + 1, this_y)
        set_velocity(this, -vel_x, vel_y)
      end,
      right = function()
        set_position(this, this_x - 1, this_y)
        set_velocity(this, -vel_x, vel_y)
      end
    }

    local action = collision_actions[collision_type]
    if action then
      action()
    end
  end
end
