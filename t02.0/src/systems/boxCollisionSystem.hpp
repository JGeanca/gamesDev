#ifndef BOX_COLLISION_SYSTEM_HPP
#define BOX_COLLISION_SYSTEM_HPP

#include "../components/boxColliderComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../utils/debug.hpp"

/**
 * @class BoxCollisionSystem
 * @brief This class represents the box collision system of the game.
 * @details Box collision system is responsible for detecting box collisions
 * between entities of the game.
 */
class BoxCollisionSystem : public System {
 private:
  bool checkAABBCollision(float aX, float aY, float aW, float aH, float bX,
                          float bY, float bW, float bH) {
    return (aX < bX + bW && aX + aW > bX && aY < bY + bH && aY + aH > bY);
  }

 public:
  /**
   * @brief BoxCollisionSystem constructor
   * @details This constructor requires the BoxColliderComponent and
   * TransformComponent to be present in the entity. **Requires means that the
   * entity must have these components to be processed by the system.
   */
  BoxCollisionSystem() {
    requireComponent<BoxColliderComponent>();
    requireComponent<TransformComponent>();
  }

  /**
   * @brief Update the collision system.
   * @details This method detects box collisions between entities of the game
   */
  void update() {
    auto entities = getEntities();
    for (auto i = entities.begin(); i != entities.end(); ++i) {
      auto& entityA = *i;
      auto& boxColliderA = entityA.getComponent<BoxColliderComponent>();
      auto& transformA = entityA.getComponent<TransformComponent>();

      for (auto j = i; j != entities.end(); ++j) {
        auto& entityB = *j;

        if (entityA == entityB) {
          continue;
        }

        auto& boxColliderB = entityB.getComponent<BoxColliderComponent>();
        auto& transformB = entityB.getComponent<TransformComponent>();

        bool collision = checkAABBCollision(
            transformA.position.x, transformA.position.y,
            static_cast<float>(boxColliderA.width),
            static_cast<float>(boxColliderA.height), transformB.position.x,
            transformB.position.y, static_cast<float>(boxColliderB.width),
            static_cast<float>(boxColliderB.height));

        if (collision) {
          DEBUG_MSG(
              "[BoxCollisionSys] Box Collision detected between entities: " +
              std::to_string(entityA.getId()) + " and " +
              std::to_string(entityB.getId()));
        }
      }
    }
  }
};

#endif  // BOX_COLLISION_SYSTEM_HPP