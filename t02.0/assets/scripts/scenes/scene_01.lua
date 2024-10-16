dofile("assets/scripts/general/game_state.lua")
local shared = dofile("assets/scripts/general/game_functions.lua")
local pauseScript = "./assets/scripts/general/pause_text.lua"
local menuScript = "./assets/scripts/menu/go_to_menu.lua"

scene = {
  collected_points = 0,
  is_paused = false,
  point_positions = {
    { x = 320, y = 300 },
    { x = 500, y = 300 },
    { x = 570, y = 150 },
    { x = 190, y = 440 },

  },
  total_points = 4,
  point_entities = {},
  victory_point_id = nil,
  victory_point_pos = { x = 670, y = 300 },
  next_level = "level_02",
  pj_reset_pos = { x = 90, y = 300 },

  sprites = {
    [0] =
        shared.sprite("enemy_1", "./assets/images/enemy_1.png"),
    shared.sprite("player_ship", "./assets/images/player_ship.png"),
    shared.sprite("background", "./assets/images/background_space_ammo_8.png"),
    shared.sprite("barrier", "./assets/images/barrier.png"),
    shared.sprite("flag_point", "./assets/images/flag_point.png"),
    shared.sprite("victory_point", "./assets/images/pick_ups.png"),
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
      shoot = "./assets/audio/sfx/shoot_01.wav",
      point = "./assets/audio/sfx/point.wav",
    },
    music = {
      level_song = "./assets/audio/music/Boss.mp3",
    }
  },

  mouse_buttons = {
    [0] =
    { name = "left", key = 1 },
  },

  entities = {
    [0] =
        shared.init_component(),
    shared.background(2000, 2000, "background"),
    shared.player(90, 300),
    shared.text("Level 1", "press_start_2p_20", 150, 0, 150, 255, 650.0, 10.0),
    shared.text("Menu", "press_start_2p_18", 150, 0, 150, 255, 10.0, 10.0, menuScript),
    shared.text("Game Paused", "press_start_2p_x", 97, 0, 250, 1, 230.0, 300.0, pauseScript),
  }
}

local start_x = 100
local start_y = 100
local sep = 42

shared.create_horizontal_barrier_row(12, start_x, start_y, sep)
shared.create_horizontal_barrier_row(12, start_x, start_y + sep * 9, sep)

shared.create_vertical_barrier_column(4, start_x, start_y - sep, sep)
shared.create_vertical_barrier_column(4, start_x, start_y + sep * 5, sep)

shared.create_vertical_barrier_column(4, start_x + sep * 13, start_y - sep, sep)
shared.create_vertical_barrier_column(4, start_x + sep * 13, start_y + sep * 5, sep)

shared.create_horizontal_barrier_row(2, start_x - sep * 3, start_y + sep * 3, sep)
shared.create_horizontal_barrier_row(2, start_x - sep * 3, start_y + sep * 6, sep)

shared.create_horizontal_barrier_row(2, start_x + sep * 13, start_y + sep * 3, sep)
shared.create_horizontal_barrier_row(2, start_x + sep * 13, start_y + sep * 6, sep)

shared.create_vertical_barrier_column(2, start_x - sep * 2, start_y + sep * 3, sep)
shared.create_vertical_barrier_column(2, start_x + sep * 15, start_y + sep * 3, sep)

--local speed = 360
local speed = 0
shared.create_bouncing_enemies(6, start_x + sep + 9, start_y + sep + 2, sep * 2, 0, 0, speed, 1.5, 1.5, 16)
shared.create_bouncing_enemies(6, start_x + sep * 2 + 9, start_y + sep * 8 + 15, sep * 2, 0, 0, -speed, 1.5, 1.5, 16)
