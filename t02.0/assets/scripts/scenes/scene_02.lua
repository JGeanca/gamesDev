dofile("assets/scripts/general/game_state.lua")
local shared = dofile("assets/scripts/general/game_functions.lua")

local pauseScript = "./assets/scripts/general/pause_text.lua"
local menuScript = "./assets/scripts/menu/go_to_menu.lua"

scene = {
  collected_points = 0,
  is_paused = false,
  point_positions = {
    { x = 404, y = 320 },
    { x = 404, y = 270 },
    { x = 360, y = 270 },
    { x = 360, y = 320 },
  },
  total_points = 4,
  point_entities = {},
  victory_point_id = nil,
  victory_point_pos = { x = 550, y = 130 },

  next_level = "level_03",

  pj_reset_pos = { x = 210, y = 130 },

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
      check_point = "./assets/audio/sfx/check_point.wav",
    },
    music = {
      level_song = "./assets/audio/music/Judgment X .mp3",
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
    shared.player(210, 130),
    shared.text("Level 2", "press_start_2p_20", 0, 255, 0, 255, 650.0, 15.0),
    shared.text("Menu", "press_start_2p_20", 255, 255, 0, 255, 10.0, 15.0, menuScript),
    shared.text("Game Paused", "press_start_2p_x", 255, 0, 0, 1, 230.0, 300.0, pauseScript),
  }
}


local start_x = 230
local start_y = 58
local sep = 42

shared.create_horizontal_barrier_row(6, start_x, start_y + sep * 11, sep)            -- bot

shared.create_vertical_barrier_column(4, start_x + sep * 7, start_y + sep * 7, sep)  -- right
shared.create_vertical_barrier_column(4, start_x, start_y + sep * 7, sep)            -- left

shared.create_horizontal_barrier_row(3, start_x - sep * 4, start_y + sep * 8, sep)   -- bot-left
shared.create_horizontal_barrier_row(3, start_x + sep * 7, start_y + sep * 8, sep)   -- bot-right

shared.create_vertical_barrier_column(4, start_x - sep * 3, start_y + sep * 3, sep)  -- left-left
shared.create_vertical_barrier_column(4, start_x + sep * 10, start_y + sep * 3, sep) -- right-right

shared.create_vertical_barrier_column(3, start_x + sep * 2, start_y + sep * 3, sep)
shared.create_vertical_barrier_column(3, start_x + sep * 5, start_y + sep * 3, sep)

shared.create_horizontal_barrier_row(1, start_x - sep * 3, start_y + sep * 3, sep) -- block - left
shared.create_horizontal_barrier_row(1, start_x, start_y + sep * 3, sep)           -- block - left-right
shared.create_horizontal_barrier_row(1, start_x + sep * 5, start_y + sep * 3, sep) -- block - right-left
shared.create_horizontal_barrier_row(1, start_x + sep * 8, start_y + sep * 3, sep) -- block - right-right

shared.create_horizontal_barrier_row(2, start_x + sep * 2, start_y + sep * 4, sep) -- center

shared.create_horizontal_barrier_row(4, start_x - sep * 3, start_y, sep)           -- top left
shared.create_horizontal_barrier_row(4, start_x + sep * 5, start_y, sep)           -- top right

shared.create_vertical_barrier_column(2, start_x - sep * 3, start_y, sep)
shared.create_vertical_barrier_column(2, start_x + sep * 2, start_y, sep)

shared.create_vertical_barrier_column(2, start_x + sep * 5, start_y, sep)
shared.create_vertical_barrier_column(2, start_x + sep * 10, start_y, sep)

local speed = 150
local hit_box = 14
local scale = 1.12


shared.create_bouncing_enemies(2, 155, start_y + sep * 4 + 12, 0, sep * 2, speed, 0, scale, scale, hit_box)
shared.create_bouncing_enemies(1, 286, start_y + sep * 5 + 12, 0, 0, -speed, 0, scale, scale, hit_box)

shared.create_bouncing_enemies(2, 155 + sep * 8, start_y + sep * 4 + 12, 0, sep * 2, speed, 0, scale, scale, hit_box)
shared.create_bouncing_enemies(1, 286 + sep * 8, start_y + sep * 5 + 12, 0, 0, -speed, 0, scale, scale, hit_box)

shared.create_bouncing_enemies(2, 285, 490, sep * 5, 0, 0, -speed, scale, scale, hit_box)

shared.create_bouncing_enemies(2, 326, 360, sep * 3, 0, 0, speed, scale, scale, hit_box)

shared.create_bouncing_enemies(1, 390, 362, sep * 3, 0, -(speed - 50), 0, scale, scale, hit_box)
shared.create_bouncing_enemies(1, 390, 362, sep * 3, 0, speed - 50, 0, scale, scale, hit_box)

shared.create_bouncing_enemies(1, 410, 280, sep * 3, 0, 0, 60, scale, scale, hit_box)
shared.create_bouncing_enemies(1, 370, 490, sep * 3, 0, 0, -60, scale, scale, hit_box)
