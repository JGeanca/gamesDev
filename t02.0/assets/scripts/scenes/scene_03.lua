dofile("assets/scripts/general/game_state.lua")
local shared = dofile("assets/scripts/general/game_functions.lua")

local pauseScript = "./assets/scripts/general/pause_text.lua"
local menuScript = "./assets/scripts/menu/go_to_menu.lua"

scene = {
  collected_points = 0,
  is_paused = false,
  point_positions = {
    { x = 330, y = 360 },
  },
  total_points = 1,
  point_entities = {},
  victory_point_id = nil,
  victory_point_pos = { x = 100, y = 430 },
  next_level = "win_scene",

  circles = {
    { x = 230, y = 170, radius = 60 },
    { x = 430, y = 170, radius = 60 },
    { x = 630, y = 185, radius = 73 },
    { x = 600, y = 450, radius = 90 },
    { x = 300, y = 450, radius = 90 },
  },
  circles_num = 5,

  pj_reset_pos = { x = 80, y = 140 },
  --pj_reset_pos = { x = 300, y = 500 },
  --pj_reset_pos = { x = 400, y = 400 },

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
      level_song = "./assets/audio/music/contra_jungle_song.mp3",
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
    shared.check_point(630, 320),
    shared.player(80, 140),
    shared.text("Level 3", "press_start_2p_20", 0, 255, 0, 255, 650.0, 15.0),
    shared.text("Menu", "press_start_2p_20", 255, 255, 0, 255, 10.0, 15.0, menuScript),
    shared.text("Game Paused", "press_start_2p_x", 255, 0, 0, 1, 230.0, 300.0, pauseScript),
  }
}

local start_x = 58
local start_y = 58
local sep = 42

shared.create_horizontal_barrier_row(15, start_x, start_y, sep)                   -- top
shared.create_horizontal_barrier_row(15, start_x, start_y + sep * 11, sep)        -- bot

shared.create_vertical_barrier_column(12, start_x + sep * 15, start_y - sep, sep) -- right
shared.create_vertical_barrier_column(12, start_x, start_y - sep, sep)            -- left

shared.create_horizontal_barrier_row(12, start_x, start_y + sep * 5, sep)         -- center top
shared.create_horizontal_barrier_row(12, start_x, start_y + sep * 6, sep)         --center bot


vel = 300
shared.create_bouncing_enemies(1, 110, 330, 100, 0, 0, vel, 1.2, 1.2, 16)

for i = 1, scene.circles_num do
  shared.create_rotating_circle(scene.circles[i].x, scene.circles[i].y, scene.circles[i].radius, i)
end
