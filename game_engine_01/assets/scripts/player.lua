-- Global variables --

player_velocity = 150;

function update()
  set_velocity(this, 0, 0)
  vel_x = 0;
  vel_y = 0;

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
  vel_x = vel_x * player_velocity
  vel_y = vel_y * player_velocity
  set_velocity(this, vel_x, vel_y)
end
