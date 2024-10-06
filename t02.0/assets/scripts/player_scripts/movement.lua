-- Global variables --
player_velocity = 200

-- Calculate the fixed player velocity for diagonal movement
-- Using math.sqrt instead of math.sqr
fixed_player_velocity = math.sqrt((player_velocity * player_velocity) / 2)

function update()
  local vel_x = 0
  local vel_y = 0

  if is_action_activated("up") then
    vel_y = vel_y - 1
  end
  if is_action_activated("down") then
    vel_y = vel_y + 1
  end
  if is_action_activated("left") then
    vel_x = vel_x - 1
  end
  if is_action_activated("right") then
    vel_x = vel_x + 1
  end

  -- Normalize the velocity vector if the player is moving diagonally
  if vel_x ~= 0 and vel_y ~= 0 then
    vel_x = vel_x * fixed_player_velocity
    vel_y = vel_y * fixed_player_velocity
  else
    vel_x = vel_x * player_velocity
    vel_y = vel_y * player_velocity
  end

  set_velocity(this, vel_x, vel_y)
end

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
