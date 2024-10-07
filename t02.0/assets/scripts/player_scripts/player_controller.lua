local movement = require("movement")
local player_collision = require("player_collision")

function update()
  movement.update()
end

function on_collision(other)
  player_collision.on_collision(other)
end
