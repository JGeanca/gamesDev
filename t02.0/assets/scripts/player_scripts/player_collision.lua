function on_collision(other)
  this_tag = get_tag(this)
  other_tag = get_tag(other)

  if other_tag == "barrier_vertical" then
    this_x, this_y = get_position(this)
    this_vel_x, this_vel_y = get_velocity(this)
    this_width, this_height = get_size(this)

    other_x, other_y = get_position(other)
    other_width, other_height = get_size(other)

    if left_collision(this, other) then
      print("Left collision with barrier")
      set_position(this, other_x + other_width + 1, this_y)
    end

    if right_collision(this, other) then
      set_position(this, other_x - this_width - 1, this_y)
    end
  end

  if other_tag == "barrier_horizontal" then
    this_x, this_y = get_position(this)
    this_vel_x, this_vel_y = get_velocity(this)
    this_width, this_height = get_size(this)

    other_x, other_y = get_position(other)
    other_width, other_height = get_size(other)

    if top_collision(this, other) then
      set_position(this, this_x, other_y + other_height + 1)
      print("Top collision with barrier")
    end

    if bottom_collision(this, other) then
      set_position(this, this_x, other_y - this_height - 1)
      print("Bottom collision with barrier")
    end
  end
end
