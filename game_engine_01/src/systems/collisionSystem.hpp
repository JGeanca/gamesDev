#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include <iostream>
#include <memory>

#include "../components/circleColliderComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../eventManager/eventManager.hpp"
#include "../events/collisionEvent.hpp"

/**
 * @class CollisionSystem
 * @brief This class represents the collision system of the game.
 * @details Collision system is responsible for detecting collisions between
 * entities of the game.
 */
class CollisionSystem : public System {
 public:
  /**
   * @brief CollisionSystem constructor
   * @details This constructor requires the CircleColliderComponent and
   * TransformComponent to be present in the entity. **Requires means that the
   * entity must have these components to be processed by the system.
   */
  CollisionSystem() {
    requireComponent<CircleColliderComponent>();
    requireComponent<TransformComponent>();
  }

  /**
   * @brief Update the collision system.
   * @param eventManager Event manager
   * @details This method detects collisions between entities of the game. The
   * collision is detected by checking the distance between the center of the
   * circle colliders and the sum of their radius.
   */
  void update(std::unique_ptr<EventManager>& eventManager) {
    auto entities = getEntities();
    for (auto i = entities.begin(); i != entities.end(); ++i) {
      auto& entityA = *i;
      auto& circleColliderA = entityA.getComponent<CircleColliderComponent>();
      auto& transformA = entityA.getComponent<TransformComponent>();

      for (auto j = i; j != entities.end(); ++j) {
        auto& entityB = *j;

        if (entityA == entityB) {
          continue;
        }

        auto& circleColliderB = entityB.getComponent<CircleColliderComponent>();
        auto& transformB = entityB.getComponent<TransformComponent>();

        glm::vec2 centerPosA =
            glm::vec2(transformA.position.x +
                          circleColliderA.width / 2 * transformA.scale.x,
                      transformA.position.y +
                          circleColliderA.height / 2 * transformA.scale.y);

        glm::vec2 centerPosB =
            glm::vec2(transformB.position.x +
                          circleColliderB.width / 2 * transformB.scale.x,
                      transformB.position.y +
                          circleColliderB.height / 2 * transformB.scale.y);

        int radiusA = circleColliderA.radius * transformA.scale.x;
        int radiusB = circleColliderB.radius * transformB.scale.x;

        bool collision =
            checkCircularCollision(radiusA, radiusB, centerPosA, centerPosB);

        if (collision) {
          eventManager->emitEvent<CollisionEvent>(entityA, entityB);
        }
      }
    }
  }

  /**
   * @brief Check circular collision
   * @param radiusA Radius of the first circle collider
   * @param radiusB Radius of the second circle collider
   * @param centerPosA Center position of the first circle collider
   * @param centerPosB Center position of the second circle collider
   * @details This method checks if two circles are colliding by comparing the
   * distance between their center positions and the sum of their radius.
   * Pitágoras theorem is used to calculate the distance between the center
   * positions.
   * @return true if the circles are colliding, false otherwise
   */
  bool checkCircularCollision(int radiusA, int radiusB, glm::vec2 centerPosA,
                              glm::vec2 centerPosB) {
    glm::vec2 distanceVec = centerPosA - centerPosB;
    float distance = glm::sqrt(distanceVec.x * distanceVec.x +
                               distanceVec.y * distanceVec.y);

    return distance <= (radiusA + radiusB);
  }
};

#endif  // COLLISION_SYSTEM_HPP