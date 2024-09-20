scene = {
  sprites = {
    [0] =
    {assetId = "enemy_1", filePath = "./assets/images/enemy_1.png"},
    {assetId = "player_ship", filePath = "./assets/images/player_ship.png"},
  },
  -- TODO: Fonts
  keys = {
    [0] = 
    {name = "left", key = 97},
    {name = "right", key = 100},
    {name = "up", key = 119},
    {name = "down", key = 115}, 
  },
  -- TODO: Mouse buttons
  -- TODO: Entities
  entities = {
    -- Player
    [0] =
    {
      components = {
        circle_collider = {
          radius = 8,
          width = 16,
          height = 16,
        },
        sprite = {
          assetId = "player_ship",
          width = 16,
          height = 16,
          src_rect = {x = 16, y = 0},
        },
        transform = {
          position = {x = 400.0, y = 300.0},
          scale = {x = 2.0, y = 2.0},
          rotation = 0.0,
        },
        script = {
          path = "./assets/scripts/player.lua"
        },
        rg_body = {
          velocity = {x = 0.0, y = 0.0},
        },            
      }
    }
  }
}