local shared = dofile("assets/scripts/general/game_functions.lua")
local menuScript = "./assets/scripts/menu/go_to_menu.lua"

scene = {
  sprites = {
    [0] =
        shared.sprite("background", "./assets/images/background_menu.png"),
    shared.sprite("flag_point", "./assets/images/flag_point.png"),
    shared.sprite("victory_point", "./assets/images/pick_ups.png"),
  },

  fonts = {
    [0] =
        shared.font("press_start_2p_24", "./assets/fonts/press_start_2p.ttf", 24),
    shared.font("press_start_2p_20", "./assets/fonts/press_start_2p.ttf", 20),
    shared.font("press_start_2p_15", "./assets/fonts/press_start_2p.ttf", 15),
  },

  keys = {
  },

  audio = {
    sound_effects = {
      selection = "./assets/audio/sfx/selection.wav",
    },
    music = {
      level_song = "./assets/audio/music/Barracks X.mp3",
    }
  },

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  entities = {
    [0] =
        shared.init_component(),
    shared.background(800, 1000, "background"),
    shared.text("Back to menu", "press_start_2p_15", 255, 0, 0, 255, 585.0, 20.0, menuScript),
    shared.text("Controls", "press_start_2p_24", 0, 255, 0, 255, 300.0, 15.0),
    shared.text("WASD to move", "press_start_2p_20", 150, 200, 0, 255, 50.0, 75.0),
    shared.text("Press P to pause", "press_start_2p_20", 150, 200, 0, 255, 50.0, 125.0),
    shared.text("Press M to mute", "press_start_2p_20", 150, 200, 0, 255, 50.0, 175.0),
    shared.text("Press Esc to quit", "press_start_2p_20", 150, 200, 0, 255, 50.0, 225.0),
    shared.text("Game", "press_start_2p_24", 0, 255, 0, 255, 340.0, 300.0),
    shared.text("Collect all the points ->", "press_start_2p_20", 150, 200, 0, 255, 50.0, 350.0),
    shared.text("and reach the win flag ->", "press_start_2p_20", 150, 200, 0, 255, 50.0, 400.0),
    shared.text("Check points           ->", "press_start_2p_20", 150, 200, 0, 255, 50.0, 450.0),
    shared.flag_point(560, 342),
    shared.victory_point(560, 392),
    shared.check_point(560, 442),
  }
}
