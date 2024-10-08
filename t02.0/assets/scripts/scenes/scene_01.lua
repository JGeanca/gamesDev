scene = {
  sprites = {
    [0] =
    { assetId = "enemy_1", filePath = "./assets/images/enemy_1.png" },
    { assetId = "player_ship", filePath = "./assets/images/player_ship.png" },
    { assetId = "background",  filePath = "./assets/images/background_space_ammo_8.png" },
    { assetId = "barrier",     filePath = "./assets/images/barrier.png" },
  },

  fonts = {
    [0] =
    { fontId = "press_start_2p_20", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 20 },
    { fontId = "press_start_2p_18", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 18 },
    { fontId = "press_start_2p_x",  filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 32 },

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
    { -- BACKGROUND
      components = {
        sprite = {
          assetId = "background",
          width = 2000,
          height = 2000,
          src_rect = { x = 500, y = 0 },
        },
        transform = {
          position = { x = 0.0, y = 0.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      }
    },
    {
      components = {
        tag = {
          tag = "player",
        },
        camera_follow = {},
        health = {
          max_health = 100,
          regeneration_rate = 1,
        },
        box_collider = {
          width = 16 * 2,
          height = 16 * 2,
          offset = { x = 0.0, y = 0.0 },
        },
        sprite = {
          assetId = "player_ship",
          width = 16,
          height = 16,
          src_rect = { x = 16, y = 0 },
        },
        transform = {
          position = { x = 400.0, y = 300.0 },
          scale = { x = 2.0, y = 2.0 },
          rotation = 0.0,
        },
        script = {
          "./assets/scripts/player_scripts/movement.lua",
          "./assets/scripts/player_scripts/player_collision.lua",

        },
        rg_body = {
          velocity = { x = 0.0, y = 0.0 },
        },
      },
    },

    { -- Enemy
      components = {
        tag = {
          tag = "enemy",
        },
        health = {
          max_health = 100,
          regeneration_rate = 0,
        },
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
        animation = {
          num_frames = 6,
          speed_rate = 10,
          is_loop = true,
        },
        transform = {
          position = { x = 400.0, y = 70.0 },
          scale = { x = 2.0, y = 2.0 },
          rotation = 0.0,
        },
        rg_body = {
          velocity = { x = 0.0, y = 0.0 },
        },
        script = {
          "./assets/scripts/enemy_scripts/basic_enemy.lua",
          "./assets/scripts/player_scripts/player_collision.lua",
        },
      }
    },
    { -- Enemy
      components = {
        tag = {
          tag = "enemy",
        },
        health = {
          max_health = 100,
          regeneration_rate = 0,
        },
        box_collider = {
          width = 16 * 2,
          height = 16 * 2,
          offset = { x = 0, y = 0 },
        },
        sprite = {
          assetId = "enemy_1",
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
          position = { x = 500.0, y = 500.0 },
          scale = { x = 2.0, y = 2.0 },
          rotation = 0.0,
        },
        rg_body = {
          velocity = { x = 0.0, y = 0.0 },
        },
        script = {
          path = "./assets/scripts/enemy_scripts/basic_enemy.lua",
        },
      }
    },
    { -- Barrier
      components = {
        tag = {
          tag = "barrier",
        },
        box_collider = {
          width = 16 * 2,
          height = 16 * 2,
          offset = { x = 0, y = 0 },
        },
        sprite = {
          assetId = "barrier",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
        },
        transform = {
          position = { x = 128.0, y = 100.0 },
          scale = { x = 2.0, y = 2.0 },
          rotation = 0.0,
        },
      }
    },
    { -- Barrier
      components = {
        tag = {
          tag = "barrier",
        },
        box_collider = {
          width = 16 * 2,
          height = 16 * 2,
          offset = { x = 0, y = 0 },
        },
        sprite = {
          assetId = "barrier",
          width = 16,
          height = 16,
          src_rect = { x = 0, y = 0 },
        },
        transform = {
          position = { x = 100.0, y = 68.0 },
          scale = { x = 2.0, y = 2.0 },
          rotation = 0.0,
        },
      }
    },
    { -- UI
      components = {
        text = {
          text = "Level 1",
          fontId = "press_start_2p_20",
          r = 150,
          g = 0,
          b = 150,
          a = 255,
        },
        transform = {
          position = { x = 650.0, y = 10.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      }
    },
    {
      components = {
        clickable = {
        },
        text = {
          text = "Menu",
          fontId = "press_start_2p_18",
          r = 150,
          g = 0,
          b = 150,
          a = 255,
        },
        transform = {
          position = { x = 10.0, y = 10.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      }
    },
    { -- Texto de pausa
      components = {
        text = {
          text = "Game Paused",
          fontId = "press_start_2p_x",
          r = 97,
          g = 0,
          b = 250,
          a = 1,
        },
        transform = {
          position = { x = 230, y = 200.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        script = {
          path = "./assets/scripts/general/pause_text.lua"
        },
      }
    },
  }
}
