local pauseScript = "./assets/scripts/general/pause_text.lua"

local function barrier(x, y)
  return {
    components = {
      tag = { tag = "barrier" },
      box_collider = {
        width = 32,
        height = 32,
        offset = { x = 0, y = 0 }
      },
      sprite = {
        assetId = "barrier",
        width = 16,
        height = 16,
        src_rect = { x = 0, y = 0 }
      },
      transform = {
        position = { x = x, y = y },
        scale = { x = 2.0, y = 2.0 },
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
      camera_follow = {},
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
      transform = { position = { x = 400.0, y = 300.0 }, scale = { x = 2.0, y = 2.0 }, rotation = 0.0 },
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
        scale = { x = 2.0, y = 2.0 },
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

scene = {
  sprites = {
    [0] =
        sprite("enemy_1", "./assets/images/enemy_1.png"),
    sprite("player_ship", "./assets/images/player_ship.png"),
    sprite("background", "./assets/images/background_space_ammo_8.png"),
    sprite("barrier", "./assets/images/barrier.png"),
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
      menu = "./assets/audio/music/Donkey Kong Country GB.mp3",
    }
  },

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  is_paused = false,

  entities = {
    [0] =
        background(2000, 2000, "background"),
    player(),
    enemy(100, 0, "enemy_1", 400, 70, 0, 0),
    enemy(100, 0, "enemy_1", 400, 500, 0, 0),
    text("Level 1", "press_start_2p_20", 150, 0, 150, 255, 650.0, 10.0),
    text("Menu", "press_start_2p_18", 150, 0, 150, 255, 10.0, 10.0),
    text("Game Paused", "press_start_2p_x", 97, 0, 250, 1, 230.0, 200.0, pauseScript),
  }
}

local function create_horizontal_barrier_row(num_barriers, init_x, y)
  for i = 0, num_barriers do
    scene.entities[#scene.entities + 1] = barrier(init_x + 32, y)
    init_x = init_x + 32
  end
end

local function create_vertical_barrier_column(num_barriers, init_y, x)
  for i = 0, num_barriers do
    scene.entities[#scene.entities + 1] = barrier(x, init_y + 32)
    init_y = init_y + 32
  end
end

create_horizontal_barrier_row(10, 200, 200)
create_horizontal_barrier_row(10, 200, 264)

create_vertical_barrier_column(10, 200, 200)
