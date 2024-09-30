scene = {
  sprites = {
    [0] =
    {assetId = "start", filePath = "./assets/images/start.png"},
  },

  fonts = {
    [0] = 
    {fontId = "press_start_2p_24", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 24},
    {fontId = "press_start_2p_20", filePath = "./assets/fonts/press_start_2p.ttf", fontSize = 20},
  },

  keys = {
  },

  mouse_buttons = {
    [0] = 
    {name = "left", key = 1},
    {name = "right", key = 3},
    {name = "middle", key = 2},
  },

  entities = {
    [0] =
    { -- Title
      components = {
        clickable = {
        },
        text = {
          text = "Jogo Bonito kkk",
          fontId = "press_start_2p_24",
          r = 150, g = 0, b = 150, a = 255,
        },
        transform = {
          position = {x = 550.0 / 2.0, y = 10.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },         
      },
    },
    { -- Level 1
      components = {
        clickable = {
        },
        script = {
          path = "./assets/scripts/menu/menu_button_01.lua",
        },
        text = {
          text = "Level 1",
          fontId = "press_start_2p_20",
          r = 150, g = 150, b = 0, a = 255,
        },
        transform = {
          position = {x = 50.0, y = 150.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },    
      }
    },
    { -- Level 2
      components = {
        clickable = {
        },
        script = {
          path = "./assets/scripts/menu/menu_button_02.lua",
        },
        text = {
          text = "Level 2",
          fontId = "press_start_2p_20",
          r = 150, g = 150, b = 0, a = 255,
        },
        transform = {
          position = {x = 50.0, y = 200.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },
      }
    },
    { -- Level 3
      components = {
        clickable = {
        },
        script = {
          path = "./assets/scripts/menu/menu_button_03.lua",
        },
        text = {
          text = "Level 3",
          fontId = "press_start_2p_20",
          r = 150, g = 150, b = 0, a = 255,
        },
        transform = {
          position = {x = 50.0, y = 250.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },    
      }
    }
  }
}