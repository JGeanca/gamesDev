local shared = dofile("assets/scripts/general/game_functions.lua")
local script_lvl_1 = "./assets/scripts/menu/start_level_01.lua"
local script_lvl_2 = "./assets/scripts/menu/start_level_02.lua"
local script_lvl_3 = "./assets/scripts/menu/start_level_03.lua"
local script_instructions = "./assets/scripts/menu/instructions.lua"

scene = {
  sprites = {
    [0] =
        shared.sprite("background", "./assets/images/background_menu.png"),

  },

  fonts = {
    [0] =
        shared.font("press_start_2p_24", "./assets/fonts/press_start_2p.ttf", 24),
    shared.font("press_start_2p_20", "./assets/fonts/press_start_2p.ttf", 20),
  },

  keys = {
  },

  audio = {
    sound_effects = {
      selection = "./assets/audio/sfx/selection.wav",
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
        shared.init_component(),
    shared.background(800, 1000, "background"),
    shared.text("Annoying Game", "press_start_2p_24", 0, 255, 0, 255, 250.0, 15.0),
    shared.text("Level 1", "press_start_2p_20", 150, 200, 0, 255, 50.0, 150.0, script_lvl_1),
    shared.text("Level 2", "press_start_2p_20", 150, 200, 0, 255, 50.0, 225.0, script_lvl_2),
    shared.text("Level 3", "press_start_2p_20", 150, 200, 0, 255, 50.0, 300.0, script_lvl_3),
    shared.text("Instructions", "press_start_2p_20", 50, 255, 100, 255, 275.0, 400.0, script_instructions),
  }
}
