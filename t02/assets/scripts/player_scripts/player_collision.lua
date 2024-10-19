dofile("assets/scripts/general/game_state.lua")
local shared = dofile("assets/scripts/general/game_functions.lua")

shared.create_points()

function on_collision(other)
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
  elseif string.sub(other_tag, 1, 5) == "enemy" then
    set_position(this, scene.pj_reset_pos.x, scene.pj_reset_pos.y) -- reset player position
    play_sound("shoot")
    game_state.total_deaths = game_state.total_deaths + 1
    kill_entity_by_id(game_state.deaths_id)
    game_state.deaths_id = create_text_entity(300, 15, "Deaths: " .. game_state.total_deaths, "press_start_2p_20", 30,
      "dd_txt")
    reset_points()
    reset_victory_point()
  elseif other_tag == "flag_point" then
    kill_entity(other)
    scene.collected_points = scene.collected_points + 1
    play_sound("point")
    if scene.collected_points == scene.total_points then
      shared.create_victory_point()
    end
  elseif other_tag == "victory_point" then
    go_to_scene(scene.next_level)
  elseif other_tag == "check_point" then
    local checkpoint_x, checkpoint_y = get_position(other)
    scene.pj_reset_pos = { x = checkpoint_x, y = checkpoint_y }
    kill_entity(other)
    play_sound("check_point")
  end
end

function reset_points()
  scene.collected_points = 0
  for i = 0, scene.total_points - 1 do
    local point_id = scene.point_entities[i + 1]
    if entity_exists_by_id(point_id) == 1 then
      kill_entity_by_id(point_id)
    end
  end

  scene.point_entities = {}
  shared.create_points()
end

function reset_victory_point()
  if scene.victory_point_id ~= nil then
    kill_entity_by_id(scene.victory_point_id)
    scene.victory_point_id = nil
  end
end
