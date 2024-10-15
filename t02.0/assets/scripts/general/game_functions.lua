local shared = {}

-- Entities functions
function shared.barrier(x, y)
  return {
    components = {
      tag = { tag = "barrier" },
      box_collider = {
        width = 42,
        height = 42,
        offset = { x = 0, y = 0 }
      },
      sprite = {
        assetId = "barrier",
        width = 42,
        height = 42,
        src_rect = { x = 0, y = 0 }
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = 1.0, y = 1.0 },
        rotation = 0.0
      }
    }
  }
end

function shared.sprite(assetId, path)
  return {
    assetId = assetId, filePath = path
  }
end

function shared.font(fontId, path, fontSize)
  return {
    fontId = fontId, filePath = path, fontSize = fontSize
  }
end

function shared.player(x, y)
  return {
    components = {
      tag = { tag = "player" },
      health = { max_health = 100, regeneration_rate = 1 },
      box_collider = {
        width = 16 * 2,
        height = 16 * 2,
        offset = { x = 0.0, y = 0.0 }
      },
      sprite = {
        assetId = "player_ship",
        width = 16,
        height = 16,
        src_rect = { x = 16, y = 0 }
      },
      transform = { position = { x = x, y = y }, scale = { x = 2.0, y = 2.0 }, rotation = 0.0 },
      script = {
        "./assets/scripts/player_scripts/movement.lua",
        "./assets/scripts/player_scripts/player_collision.lua"
      },
      rg_body = { velocity = { x = 0.0, y = 0.0 } }
    }
  }
end

function shared.background(w, h, assetId)
  return {
    components = {
      sprite = {
        assetId = assetId,
        width = w,
        height = h,
        src_rect = { x = 500, y = 0 },
      },
      transform = {
        position = { x = 0.0, y = 0.0 },
        scale = { x = 1.0, y = 1.0 },
        rotation = 0.0,
      },
    }
  }
end

function shared.text(msg, fontId, r, g, b, a, x, y, script)
  local result = {
    components = {
      clickable = {
      },
      text = {
        text = msg,
        fontId = fontId,
        r = r,
        g = g,
        b = b,
        a = a,
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = 1.0, y = 1.0 },
        rotation = 0.0,
      },
    },
  }
  if script then
    result.components.script = { script }
  end
  return result
end

function shared.enemy_bounce(assetId, x, y, vel_x, vel_y, scale_x, scale_y, hit_box)
  return {
    components = {
      tag = {
        tag = "enemy",
      },
      health = {
        max_health = 100,
        regeneration_rate = 0,
      },
      box_collider = {
        width = hit_box * 2,
        height = hit_box * 2,
        offset = { x = 0.0, y = 0.0 },
      },
      sprite = {
        assetId = assetId,
        width = 16,
        height = 16,
        src_rect = { x = 16, y = 0 },
      },
      animation = {
        num_frames = 6,
        speed_rate = 10,
        is_loop = true,
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = scale_x, y = scale_y },
        rotation = 0.0,
      },
      rg_body = {
        velocity = { x = vel_x, y = vel_y },
      },
      script = {
        "./assets/scripts/enemy_scripts/basic_enemy.lua",
      },
    }
  }
end

function shared.circular_enemy(tag, x, y, formation_index)
  return {
    components = {
      tag = { tag = tag .. "_" .. formation_index },
      health = { max_health = 100, regeneration_rate = 0 },
      box_collider = {
        width = 16 * 2,
        height = 16 * 2,
        offset = { x = 0.0, y = 0.0 },
      },
      sprite = {
        assetId = "enemy_1",
        width = 16,
        height = 16,
        src_rect = { x = 16, y = 0 },
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = 1.2, y = 1.2 },
        rotation = 0.0,
      },
      rg_body = {
        velocity = { x = 0, y = 0 },
      },
      script = {
        "./assets/scripts/enemy_scripts/circle_enemy.lua",
      },
      animation = {
        num_frames = 6,
        speed_rate = 10,
        is_loop = true,
      },
    },
  }
end

function shared.victory_point(x, y)
  return {
    components = {
      tag = {
        tag = "victory_point",
      },
      box_collider = {
        width = 16 * 2,
        height = 16 * 2,
        offset = { x = 0.0, y = 0.0 },
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = 2.0, y = 2.0 },
        rotation = 0.0,
      },
      sprite = {
        assetId = "flag_point",
        width = 16,
        height = 16,
        src_rect = { x = 32, y = 0 },
      },
    }
  }
end

function shared.flag_point(x, y)
  return {
    components = {
      tag = {
        tag = "flag_point",
      },
      box_collider = {
        width = 16 * 2,
        height = 16 * 2,
        offset = { x = 0.0, y = 0.0 },
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = 2.0, y = 2.0 },
        rotation = 0.0,
      },
      sprite = {
        assetId = "flag_point",
        width = 16,
        height = 16,
        src_rect = { x = 0, y = 0 },
      },
    }
  }
end

function shared.check_point(x, y)
  return {
    components = {
      tag = {
        tag = "check_point",
      },
      box_collider = {
        width = 16 * 2,
        height = 16 * 2,
        offset = { x = 0.0, y = 0.0 },
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = 2.0, y = 2.0 },
        rotation = 0.0,
      },
      sprite = {
        assetId = "flag_point",
        width = 16,
        height = 16,
        src_rect = { x = 32, y = 0 },
      },
    }
  }
end

function shared.init_component()
  return {
    components = {
      tag = {
        tag = "level_manager"
      },
      script = {
        path = "./assets/scripts/general/level_manager.lua",
      },
    }
  }
end

function shared.create_horizontal_barrier_row(num_barriers, init_x, y, sep)
  for i = 0, num_barriers - 1 do
    scene.entities[#scene.entities + 1] = shared.barrier(init_x + sep, y)
    init_x = init_x + sep
  end
end

function shared.create_vertical_barrier_column(num_barriers, x, init_y, sep)
  for i = 0, num_barriers - 1 do
    scene.entities[#scene.entities + 1] = shared.barrier(x, init_y + sep)
    init_y = init_y + sep
  end
end

function shared.create_bouncing_enemies(num_enemies, start_x, y, sep_x, sep_y, vel_x, vel_y, scale_x, scale_y, hit_box)
  for i = 0, num_enemies - 1 do
    scene.entities[#scene.entities + 1] = shared.enemy_bounce("enemy_1", start_x + i * sep_x, y + i * sep_y, vel_x, vel_y,
      scale_x,
      scale_y, hit_box)
  end
end

function shared.create_rotating_circle(center_x, center_y, radius, formation_index)
  local diag_fact = 0.7
  local formation = {
    shared.circular_enemy("enemy_top", center_x, center_y - radius, formation_index),
    shared.circular_enemy("enemy_bottom", center_x, center_y + radius, formation_index),
    shared.circular_enemy("enemy_left", center_x - radius, center_y, formation_index),
    shared.circular_enemy("enemy_right", center_x + radius, center_y, formation_index),
    shared.circular_enemy("enemy_topleft", center_x - radius * diag_fact, center_y - radius * diag_fact, formation_index),
    shared.circular_enemy("enemy_topright", center_x + radius * diag_fact, center_y - radius * diag_fact,
      formation_index),
    shared.circular_enemy("enemy_bottomleft", center_x - radius * diag_fact, center_y + radius * diag_fact,
      formation_index),
    shared.circular_enemy("enemy_bottomright", center_x + radius * diag_fact, center_y + radius * diag_fact,
      formation_index)
  }

  for i = 0, #formation - 1 do
    scene.entities[#scene.entities + 1] = formation[i]
  end
end

function shared.create_points()
  for i = 0, scene.total_points - 1 do
    local point_x = scene.point_positions[i + 1].x
    local point_y = scene.point_positions[i + 1].y
    local id = create_entity(point_x, point_y, 16, 16, "flag_point", "flag_point")
    scene.point_entities[#scene.point_entities + 1] = id
  end
end

function shared.create_victory_point()
  local id = create_entity(scene.victory_point_pos.x, scene.victory_point_pos.y, 16, 16, "victory_point", "victory_point")
  scene.victory_point_id = id
end

return shared
