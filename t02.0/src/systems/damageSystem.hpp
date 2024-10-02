#ifndef DAMAGE_SYSTEM_HPP
#define DAMAGE_SYSTEM_HPP

#include <memory>
#include <string>

#include "../components/circleColliderComponent.hpp"
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

  /**
   * @brief Callback for the collision event
   * @param eventManager Event manager
   * @details This is the callback function that is called when a collision.
   * If the collision is between a player and an enemy, the player is killed.
   */
  void onCollision(CollisionEvent& event) {
    Entity& entityA = event.entityA;
    Entity& entityB = event.entityB;

    std::string tagA = entityA.getComponent<TagComponent>().tag;
    std::string tagB = entityB.getComponent<TagComponent>().tag;

    DEBUG_MSG("[DamageSystem] Collision between: " + tagA + " and " + tagB);
    // TODO: Change this
    entityA.killEntity();
    entityB.killEntity();
  }
};

#endif  // DAMAGE_SYSTEM_HPP