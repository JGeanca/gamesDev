#ifndef DAMAGE_SYSTEM_HPP
#define DAMAGE_SYSTEM_HPP

#include <memory>
#include <string>

#include "../components/circleColliderComponent.hpp"
#include "../components/enemyComponent.hpp"
#include "../components/playerComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../eventManager/eventManager.hpp"
#include "../events/collisionEvent.hpp"
#include "../utils/debug.hpp"

/**
 * @class DamageSystem
 * @brief This class represents the damage system of the game.
 * @details Damage system is responsible for applying damage to entities.
 */
class DamageSystem : public System {
 public:
  /**
   * @brief DamageSystem constructor
   * @details This constructor requires the CircleColliderComponent to be
   * present in the entity. **Requires means that the entity must have this
   * component to be processed by the system.
   */
  DamageSystem() { requireComponent<CircleColliderComponent>(); }

  /**
   * @brief Suscribe the system (DamageSystem) to the collision event
   * @param eventManager Event manager
   */
  void suscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
    eventManager->subscribeToEvent<CollisionEvent, DamageSystem>(
        this, &DamageSystem::onCollision);
  }

  /**
   * @brief Check if the collision is between a player and an enemy
   * @param entityA Entity A in the collision
   * @param entityB Entity B in the collision
   * @return true if the collision is between a player and an enemy, false
   * otherwise
   */
  bool isPlayerEnemyCollision(Entity& entityA, Entity& entityB) {
    return (entityA.hasComponent<PlayerComponent>() &&
            entityB.hasComponent<EnemyComponent>()) ||
           (entityA.hasComponent<EnemyComponent>() &&
            entityB.hasComponent<PlayerComponent>());
  }

  /**
   * @brief Callback for the collision event
   * @param eventManager Event manager
   * @details This is the callback function that is called when a collision.
   * If the collision is between a player and an enemy, the player is killed.
   */
  void onCollision(CollisionEvent& event) {
    Entity& entityA = event.entityA;
    Entity& entityB = event.entityB;

    if (isPlayerEnemyCollision(entityA, entityB)) {
      Entity& player =
          entityA.hasComponent<PlayerComponent>() ? entityA : entityB;
      Entity& enemy =
          entityA.hasComponent<EnemyComponent>() ? entityA : entityB;

      DEBUG_MSG("[DamageSystem] Player collided with enemy. Player ID: " +
                std::to_string(player.getId()) +
                ", Enemy ID: " + std::to_string(enemy.getId()));
      (void)enemy;  // Enemy is just for debugging purposes
      player.killEntity();
    }

    DEBUG_MSG("[DamageSystem] Collision detected between " +
              std::to_string(event.entityA.getId()) + " and " +
              std::to_string(event.entityB.getId()));
  }
};

#endif  // DAMAGE_SYSTEM_HPP