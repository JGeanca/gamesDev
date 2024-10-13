local pauseScript = "./assets/scripts/general/pause_text.lua"
local menuScript = "./assets/scripts/menu/go_to_menu.lua"

local function barrier(x, y)
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

local function sprite(assetId, path)
  return {
    assetId = assetId, filePath = path
  }
end

local function font(fontId, path, fontSize)
  return {
    fontId = fontId, filePath = path, fontSize = fontSize
  }
end

local function player()
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
      transform = { position = { x = 80, y = 140 }, scale = { x = 2.0, y = 2.0 }, rotation = 0.0 },
      script = {
        "./assets/scripts/player_scripts/movement.lua",
        "./assets/scripts/player_scripts/player_collision.lua"
      },
      rg_body = { velocity = { x = 0.0, y = 0.0 } }
    }
  }
end

local function background(w, h, assetId)
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

local function text(msg, fontId, r, g, b, a, x, y, script)
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

local function circular_enemy(tag, x, y, formation_index)
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
    center_x = 100,
  }
end


local function enemy(max_health, regen_rate, assetId, x, y, vel_x, vel_y)
  return {
    components = {
      tag = {
        tag = "enemy",
      },
      health = {
        max_health = max_health,
        regeneration_rate = regen_rate,
      },
      box_collider = {
        width = 16 * 2,
        height = 16 * 2,
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
        scale = { x = 1.3, y = 1.3 },
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

local function victory_point(x, y)
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

function flag_point(x, y)
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

function check_point(x, y)
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

local function init_component()
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

scene = {
  collected_points = 0,
  is_paused = false,
  point_positions = {
    { x = 330, y = 360 },
  },
  total_points = 1,
  point_entities = {},
  victory_point_id = nil,
  next_level = "level_03",

  circles = {
    { x = 230, y = 170, radius = 60 },
    { x = 430, y = 170, radius = 60 },
    { x = 630, y = 185, radius = 73 },
    { x = 600, y = 450, radius = 90 },
    { x = 300, y = 450, radius = 90 },
  },
  circles_num = 5,

  --pj_reset_pos = { x = 300, y = 500 },
  pj_reset_pos = { x = 80, y = 140 },

  sprites = {
    [0] =
        sprite("enemy_1", "./assets/images/enemy_1.png"),
    sprite("player_ship", "./assets/images/player_ship.png"),
    sprite("background", "./assets/images/background_space_ammo_8.png"),
    sprite("barrier", "./assets/images/barrier.png"),
    sprite("flag_point", "./assets/images/flag_point.png"),
    sprite("victory_point", "./assets/images/pick_ups.png"),
  },

  fonts = {
    [0] =
        font("press_start_2p_20", "./assets/fonts/press_start_2p.ttf", 20),
    font("press_start_2p_18", "./assets/fonts/press_start_2p.ttf", 18),
    font("press_start_2p_x", "./assets/fonts/press_start_2p.ttf", 32),
  },

  keys = {
    [0] =
    { name = "up", key = 119 },    -- w
    { name = "left",  key = 97 },  -- a
    { name = "down",  key = 115 }, -- s
    { name = "right", key = 100 }, -- d
  },

  audio = {
    sound_effects = {
      shoot = "./assets/audio/sfx/shoot_01.wav",
      point = "./assets/audio/sfx/point.wav",
      check_point = "./assets/audio/sfx/check_point.wav",
    },
    music = {
      level_song = "./assets/audio/music/contra_jungle_song.mp3",
    }
  },

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  entities = {
    [0] =
        init_component(),
    background(2000, 2000, "background"),
    check_point(630, 320),
    player(),
    text("Level 2", "press_start_2p_20", 150, 0, 150, 255, 650.0, 10.0),
    text("Menu", "press_start_2p_18", 150, 0, 150, 255, 10.0, 10.0, menuScript),
    text("Game Paused", "press_start_2p_x", 97, 0, 250, 1, 230.0, 300.0, pauseScript),
  }
}

local function create_horizontal_barrier_row(num_barriers, init_x, y, sep)
  for i = 0, num_barriers - 1 do
    scene.entities[#scene.entities + 1] = barrier(init_x + sep, y)
    init_x = init_x + sep
  end
end

local function create_vertical_barrier_column(num_barriers, x, init_y, sep)
  for i = 0, num_barriers - 1 do
    scene.entities[#scene.entities + 1] = barrier(x, init_y + sep)
    init_y = init_y + sep
  end
end

function create_enemies(num_enemies, start_x, y, sep, vel_x, vel_y)
  for i = 0, num_enemies - 1 do
    scene.entities[#scene.entities + 1] = enemy(100, 0, "enemy_1", start_x + i * sep, y, vel_x, vel_y)
  end
end

function create_points()
  for i = 0, scene.total_points - 1 do
    local point_x = scene.point_positions[i + 1].x
    local point_y = scene.point_positions[i + 1].y
    local id = create_entity(point_x, point_y, 16, 16, "flag_point", "flag_point")
    scene.point_entities[#scene.point_entities + 1] = id
  end
end

function create_victory_point()
  local id = create_entity(100, 430, 16, 16, "victory_point", "victory_point")
  scene.victory_point_id = id
end

local start_x = 58
local start_y = 58
local sep = 42

create_horizontal_barrier_row(15, start_x, start_y, sep)                   -- top
create_horizontal_barrier_row(15, start_x, start_y + sep * 11, sep)        -- bot

create_vertical_barrier_column(12, start_x + sep * 15, start_y - sep, sep) -- right
create_vertical_barrier_column(12, start_x, start_y - sep, sep)            -- left

create_horizontal_barrier_row(12, start_x, start_y + sep * 5, sep)         -- center top
create_horizontal_barrier_row(12, start_x, start_y + sep * 6, sep)         --center bot


vel = 300
create_enemies(1, 110, 330, 100, 0, vel)

local diag_fact = 0.7

local function create_rotating_circle(center_x, center_y, radius, formation_index)
  local formation = {
    circular_enemy("enemy_top", center_x, center_y - radius, formation_index),
    circular_enemy("enemy_bottom", center_x, center_y + radius, formation_index),
    circular_enemy("enemy_left", center_x - radius, center_y, formation_index),
    circular_enemy("enemy_right", center_x + radius, center_y, formation_index),
    circular_enemy("enemy_topleft", center_x - radius * diag_fact, center_y - radius * diag_fact, formation_index),
    circular_enemy("enemy_topright", center_x + radius * diag_fact, center_y - radius * diag_fact,
      formation_index),
    circular_enemy("enemy_bottomleft", center_x - radius * diag_fact, center_y + radius * diag_fact,
      formation_index),
    circular_enemy("enemy_bottomright", center_x + radius * diag_fact, center_y + radius * diag_fact,
      formation_index)
  }

  for i = 0, #formation - 1 do
    scene.entities[#scene.entities + 1] = formation[i]
  end
end

for i = 1, scene.circles_num do
  create_rotating_circle(scene.circles[i].x, scene.circles[i].y, scene.circles[i].radius, i)
end
