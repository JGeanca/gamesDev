#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include "../components/rigidBodyComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"

/**
 * @class MovementSystem
 * @brief This class represents the movement system of the game.
 * @details Movement system is responsible for moving the entities of the game.
 */
class MovementSystem : public System {
 public:
  /**
   * @brief MovementSystem constructor
   * @details This constructor requires the TransformComponent and
   * RigidBodyComponent to be present in the entity. **Requires means that the
   * entity must have these components to be processed by the system.
   */
  MovementSystem() {
    requireComponent<TransformComponent>();
    requireComponent<RigidBodyComponent>();
  }

  /**
   * @brief Update the movement system.
   * @param deltaTime The time passed since the last frame
   * @details This method moves the entities of the game based on their
   * velocity. The velocity is calculated by the RigidBodyComponent. The
   * position is calculated by the TransformComponent.
   */
  void update(double deltaTime) {
    for (auto entity : getEntities()) {
      auto& transform = entity.getComponent<TransformComponent>();
      auto& rigidBody = entity.getComponent<RigidBodyComponent>();
      transform.position.x += rigidBody.velocity.x * deltaTime;
      transform.position.y += rigidBody.velocity.y * deltaTime;
    }
  }
};

#endif  // MOVEMENT_SYSTEM_HPP