scene = {
  sprites = {},

  fonts = {
    [0] = 
    {fontId = "highway_gothic_24", filePath = "./assets/fonts/highway_gothic.ttf", fontSize = 24},
    {fontId = "highway_gothic_32", filePath = "./assets/fonts/highway_gothic.ttf", fontSize = 32},
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
          fontId = "highway_gothic_32",
          r = 150, g = 0, b = 150, a = 255,
        },
        transform = {
          position = {x = (600.0) / 2.0, y = 0.0},
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
          fontId = "highway_gothic_24",
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
          fontId = "highway_gothic_24",
          r = 150, g = 150, b = 0, a = 255,
        },
        transform = {
          position = {x = 50.0, y = 250.0},
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
          fontId = "highway_gothic_24",
          r = 150, g = 150, b = 0, a = 255,
        },
        transform = {
          position = {x = 50.0, y = 350.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },    
      }
    }
  }
}