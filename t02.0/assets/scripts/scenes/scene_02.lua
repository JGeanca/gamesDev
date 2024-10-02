scene = {
  sprites = {
    [0] =
    {assetId = "enemy_1", filePath = "./assets/images/enemy_1.png"},
    {assetId = "player_ship", filePath = "./assets/images/player_ship.png"},
  },

  fonts = {
    [0] = 
    {fontId = "highway_gothic", filePath = "./assets/fonts/highway_gothic.ttf", fontSize = 24},
  },

  keys = {
    [0] = 
    {name = "left", key = 97},
    {name = "right", key = 100},
    {name = "up", key = 119},
    {name = "down", key = 115}, 
  },

  mouse_buttons = {
    [0] = 
    {name = "left", key = 1},
    {name = "right", key = 3},
    {name = "middle", key = 2},
  },

  entities = {
    -- Player
    [0] =
    {
      components = {
        clickable = {
        },
        text = {
          text = "LEVEL 2",
          fontId = "highway_gothic",
          r = 150, g = 0, b = 150, a = 255,
        },
        transform = {
          position = {x = 500.0, y = 50.0},
          scale = {x = 1.0, y = 1.0},
          rotation = 0.0,
        },         
      }
    }
  }
}