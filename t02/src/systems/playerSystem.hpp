#ifndef PLAYER_SYSTEM_HPP
#define PLAYER_SYSTEM_HPP

#include <iostream>

#include "../components/playerComponent.hpp"
#include "../components/rigidBodyComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../eventManager/eventManager.hpp"
#include "../events/playerKilledEvent.hpp"
#include "../utils/debug.hpp"

class PlayerSystem : public System {
 public:
  /**
   * @brief PlayerSystem constructor
   * @details This constructor requires the PlayerComponent and
   * RigidBodyComponent to be present in the entity. **Requires means that the
   * entity must have these components to be processed by the system.
   */
  PlayerSystem() {
    requireComponent<PlayerComponent>();
    requireComponent<RigidBodyComponent>();
    requireComponent<TransformComponent>();
  }

  void subscribeToPlayerKilledEvent(
      std::unique_ptr<EventManager>& eventManager) {
    eventManager->subscribeToEvent<PlayerKilledEvent, PlayerSystem>(
        this, &PlayerSystem::onPlayerKilled);
  }

  void onPlayerKilled(PlayerKilledEvent& event) {
    auto& player = event.player;

    auto& transform = player.getComponent<TransformComponent>();
    auto& rigidBody = player.getComponent<RigidBodyComponent>();
    auto& playerComponent = player.getComponent<PlayerComponent>();

    transform.position.x = playerComponent.resetPosition.x;
    transform.position.y = playerComponent.resetPosition.y;
    rigidBody.velocity = glm::vec2(0.0, 0.0);
  }
};

#endif  // PLAYER_SYSTEM_HPP