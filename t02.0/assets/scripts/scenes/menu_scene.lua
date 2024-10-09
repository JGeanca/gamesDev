scene = {
  sprites = {
    [0] =
    { assetId = "start", filePath = "./assets/images/start.png" },
  },

  fonts = {
    [0] =
    { fontId = "press_start_2p_24", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 24 },
    { fontId = "press_start_2p_20", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 20 },
  },

  keys = {
  },

  audio = {
    sound_effects = {
      shoot = "./assets/audio/sfx/shoot_01.wav",
    },
    music = {
      level_song = "./assets/audio/music/Donkey Kong Country GB.mp3",
    }
  },

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  entities = {
    [0] =
    { -- Title
      components = {
        text = {
          text = "Space Reversed Bullet Hell",
          fontId = "press_start_2p_24",
          r = 150,
          g = 0,
          b = 150,
          a = 255,
        },
        transform = {
          position = { x = 100.0, y = 10.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
      },
    },
    { -- Level 1 - Button
      components = {
        clickable = {
        },
        text = {
          text = "Level 1",
          fontId = "press_start_2p_20",
          r = 150,
          g = 150,
          b = 0,
          a = 255,
        },
        transform = {
          position = { x = 50.0, y = 150.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        script = {
          path = "./assets/scripts/menu/start_level_01.lua",
        },
      }
    },
    { -- Level 2 - Button
      components = {
        clickable = {
        },

        text = {
          text = "Level 2",
          fontId = "press_start_2p_20",
          r = 150,
          g = 150,
          b = 0,
          a = 255,
        },
        transform = {
          position = { x = 50.0, y = 200.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        script = {
          path = "./assets/scripts/menu/start_level_02.lua",
        },
      }
    },
    { -- Level 3 - Button
      components = {
        clickable = {
        },
        text = {
          text = "Level 3",
          fontId = "press_start_2p_20",
          r = 150,
          g = 150,
          b = 0,
          a = 255,
        },
        transform = {
          position = { x = 50.0, y = 250.0 },
          scale = { x = 1.0, y = 1.0 },
          rotation = 0.0,
        },
        script = {
          path = "./assets/scripts/menu/start_level_03.lua",
        },
      }
    },
    {
      components = {
        tag = {
          tag = "level_manager"
        },
        script = {
          path = "./assets/scripts/general/level_manager.lua",
        },
      }
    }
  }
}
