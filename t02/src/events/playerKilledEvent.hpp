#ifndef PLAYER_KILLED_EVENT_HPP
#define PLAYER_KILLED_EVENT_HPP

#include "../ecs/ecs.hpp"
#include "../eventManager/event.hpp"

class PlayerKilledEvent : public Event {
 public:
  Entity& player;

  PlayerKilledEvent(Entity& player) : player(player) {}
};

#endif  // PLAYER_KILLED_EVENT_HPP