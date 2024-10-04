scene = {
  sprites = {
    [0] =
    { assetId = "enemy_1", filePath = "./assets/images/enemy_1.png" },
    { assetId = "player_ship", filePath = "./assets/images/player_ship.png" },
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

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  is_paused = false,

  entities = {
    [0] =
    {
      components = {
        tag = {
          tag = "player",
        },
        health = {
          max_health = 100,
          regeneration_rate = 1,
        },
        circle_collider = {
          radius = 8,
          width = 16,
          height = 16,
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
          path = "./assets/scripts/player_scripts/movement.lua"
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
        circle_collider = {
          radius = 8,
          width = 16,
          height = 16,
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
          position = { x = 100.0, y = 100.0 },
          scale = { x = 2.0, y = 2.0 },
          rotation = 0.0,
        },
        rg_body = {
          velocity = { x = 100.0, y = 0.0 },
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
        circle_collider = {
          radius = 8,
          width = 16,
          height = 16,
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
