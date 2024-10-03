#ifndef DAMAGE_SYSTEM_HPP
#define DAMAGE_SYSTEM_HPP

#include <memory>
#include <string>

#include "../components/circleColliderComponent.hpp"
#include "../components/healthComponent.hpp"
#include "../components/tagComponent.hpp"
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

  bool isPlayerEnemyCollision(Entity& entityA, Entity& entityB) {
    std::string tagA = entityA.getComponent<TagComponent>().tag;
    std::string tagB = entityB.getComponent<TagComponent>().tag;

    return (tagA == "player" && tagB == "enemy") ||
           (tagA == "enemy" && tagB == "player");
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

    // TODO: Refactor this code
    if (entityA.hasComponent<HealthComponent>() ||
        entityB.hasComponent<HealthComponent>()) {
      if (isPlayerEnemyCollision(entityA, entityB)) {
        Entity& player = entityA.getComponent<TagComponent>().tag == "player"
                             ? entityA
                             : entityB;
        Entity& enemy = entityA.getComponent<TagComponent>().tag == "enemy"
                            ? entityA
                            : entityB;

        auto& health = player.getComponent<HealthComponent>();
        health.takeDamage(1);
        std::string healthLeft = std::to_string(health.currentHealth);
        DEBUG_MSG("Player took 1 damage, Health: " + healthLeft);
        if (health.isDead()) {
          DEBUG_MSG("Player is dead");
          player.killEntity();
        }
      }
    }
  }
};

#endif  // DAMAGE_SYSTEM_HPP