function on_collision(other)
  this_tag = get_tag(this)
  other_tag = get_tag(other)

  if other_tag == "barrier" then
    if left_collision(this, other) then
      print("Left collision with barrier")

      -- Avoid superposition
      this_x, this_y = get_position(this)
      this_vel_x, this_vel_y = get_velocity(this)
      this_width, this_height = get_size(this)

      other_x, other_y = get_position(other)
      other_width, other_height = get_size(other)

      set_position(this, other_x + other_width + 1, this_y)
    end

    if right_collision(this, other) then
      print("Right collision with barrier")
    end
  end
end
