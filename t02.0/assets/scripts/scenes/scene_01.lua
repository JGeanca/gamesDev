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
      transform = { position = { x = 90.0, y = 300.0 }, scale = { x = 2.0, y = 2.0 }, rotation = 0.0 },
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
        scale = { x = 1.5, y = 1.5 },
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
    { x = 400, y = 300 },
    { x = 500, y = 300 },
  },
  total_points = 2,
  point_entities = {},
  victory_point_id = nil,
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
    },
    music = {
      level_song = "./assets/audio/music/Aquatic Ambiance GB.mp3",
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
    player(),
    text("Level 1", "press_start_2p_20", 150, 0, 150, 255, 650.0, 10.0),
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
    local id = create_entity(400 + i * 64, 300, 16, 16, "flag_point", "flag_point")
    scene.point_entities[#scene.point_entities + 1] = id
  end
end

function create_victory_point()
  local id = create_entity(670, 300, 16, 16, "victory_point", "victory_point")
  scene.victory_point_id = id
end

local start_x = 100
local start_y = 100
local sep = 42

create_horizontal_barrier_row(12, start_x, start_y, sep)
create_horizontal_barrier_row(12, start_x, start_y + sep * 9, sep)

create_vertical_barrier_column(4, start_x, start_y - sep, sep)
create_vertical_barrier_column(4, start_x, start_y + sep * 5, sep)

create_vertical_barrier_column(4, start_x + sep * 13, start_y - sep, sep)
create_vertical_barrier_column(4, start_x + sep * 13, start_y + sep * 5, sep)

create_horizontal_barrier_row(2, start_x - sep * 3, start_y + sep * 3, sep)
create_horizontal_barrier_row(2, start_x - sep * 3, start_y + sep * 6, sep)

create_horizontal_barrier_row(2, start_x + sep * 13, start_y + sep * 3, sep)
create_horizontal_barrier_row(2, start_x + sep * 13, start_y + sep * 6, sep)

create_vertical_barrier_column(2, start_x - sep * 2, start_y + sep * 3, sep)
create_vertical_barrier_column(2, start_x + sep * 15, start_y + sep * 3, sep)



local speed = 0
create_enemies(6, start_x + sep + 9, start_y + sep + 2, sep * 2, 0, speed)
create_enemies(6, start_x + sep * 2 + 9, start_y + sep * 8 + 15, sep * 2, 0, -speed)
