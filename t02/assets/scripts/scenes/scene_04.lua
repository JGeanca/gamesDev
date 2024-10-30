local shared = dofile("assets/scripts/general/game_functions.lua")
local pauseScript = "./assets/scripts/general/pause_text.lua"
local menuScript = "./assets/scripts/menu/go_to_menu.lua"

scene = {
  is_paused = false,
  next_level = "win_scene",

  pj_reset_pos = { x = 80, y = 140 },

  sprites = {
    [0] =
        shared.sprite("enemy_1", "./assets/images/enemy_1.png"),
    shared.sprite("player_ship", "./assets/images/player_ship.png"),
    shared.sprite("background", "./assets/images/background_space_ammo_8.png"),
    shared.sprite("barrier", "./assets/images/barrier.png"),
    shared.sprite("flag_point", "./assets/images/flag_point.png"),
    shared.sprite("victory_point", "./assets/images/pick_ups.png"),
    shared.sprite("terrain", "./assets/images/terrain.png"),
  },

  fonts = {
    [0] =
        shared.font("press_start_2p_20", "./assets/fonts/press_start_2p.ttf", 20),
    shared.font("press_start_2p_18", "./assets/fonts/press_start_2p.ttf", 18),
    shared.font("press_start_2p_x", "./assets/fonts/press_start_2p.ttf", 32),
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
    },
    music = {
      level_song = "./assets/audio/music/contra_jungle_song.mp3",
    }
  },

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  maps = {
    map_path = "./assets/maps/level_01.tmx",
    tile_path = "./assets/maps/terrain.tsx",
    tile_name = "terrain",
  },

  entities = {
    [0] =
        shared.init_component(),
    --  shared.background(2000, 2000, "background"),
    --shared.player(80, 140),
    shared.text("Level 3", "press_start_2p_20", 0, 255, 0, 255, 650.0, 15.0),
    shared.text("Menu", "press_start_2p_20", 255, 255, 0, 255, 10.0, 15.0, menuScript),
    shared.text("Game Paused", "press_start_2p_x", 255, 0, 0, 1, 230.0, 300.0, pauseScript),
  }
}
