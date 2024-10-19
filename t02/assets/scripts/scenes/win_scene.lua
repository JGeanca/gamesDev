local shared = dofile("assets/scripts/general/game_functions.lua")
local menuScript = "./assets/scripts/menu/go_to_menu.lua"

scene = {
  sprites = {
    [0] =
        shared.sprite("background", "./assets/images/background_win.png"),

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
      level_song = "./assets/audio/music/Carry Out X.mp3",
    }
  },

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  entities = {
    [0] =
        shared.init_component_2(),
    shared.background(800, 600, "background"),
    shared.text("GG!", "press_start_2p_24", 0, 255, 0, 255, 375.0, 100.0),
    shared.text("Thanks for playing!", "press_start_2p_20", 0, 255, 0, 255, 200.0, 280.0),
    shared.text("Back to menu", "press_start_2p_15", 255, 0, 0, 255, 585.0, 20.0, menuScript),

  }
}
