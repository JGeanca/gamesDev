create_points()


function on_collision(other)
  local this_tag = get_tag(this)
  local other_tag = get_tag(other)
  local collision_type = get_collision_type(this, other)
  local this_x, this_y = get_position(this)

  if other_tag == "barrier" then
    local this_width, this_height = get_size(this)
    local other_x, other_y = get_position(other)
    local other_width, other_height = get_size(other)

    local collision_actions = {
      left = function()
        set_position(this, other_x + other_width + 1, this_y)
      end,
      right = function()
        set_position(this, other_x - this_width - 1, this_y)
      end,
      top = function()
        set_position(this, this_x, other_y + other_height + 1)
      end,
      bottom = function()
        set_position(this, this_x, other_y - this_height - 1)
      end
    }

    local action = collision_actions[collision_type]
    if action then
      action()
    end
  elseif other_tag == "enemy" then
    local initial_x = 90
    local initial_y = 300

    set_position(this, initial_x, initial_y) -- reset player position
    play_sound("shoot")                      --TODO Change SOUND
    reset_points()
  elseif other_tag == "flag_point" then
    kill_entity(other)
    scene.collected_points = scene.collected_points + 1
    print("Points: " .. scene.collected_points)
    -- play_sound("point") --TODO
    if currentPoints == totalPoints then
      -- show_victory_point() --TODO
    end
  end
end

function reset_points()
  scene.collected_points = 0
  for i = 0, scene.total_points - 1 do
    local point_id = scene.point_entities[i + 1]

    if entity_exists_by_id(point_id) then
      local exist = entity_exists_by_id(point_id)
      print("BEFORE KILL. Hi im: " .. point_id .. " and I " .. exist)

      kill_entity_by_id(point_id)

      exist = entity_exists_by_id(point_id)
      print("AFTER KILL. Hi im" .. point_id .. " and I " .. exist)
    else
      print("Hi im: " .. point_id .. " and I dont exist")
    end
    --   print("Just BEFORE check if exists")
    --   local exist = entity_exists(point_id)
    --   print("AFTER Hi im" .. point_id .. " and I" .. exist)
    -- else
    --   print("DOesnt exist")
    -- end
  end
end
