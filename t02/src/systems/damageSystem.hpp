#ifndef DAMAGE_SYSTEM_HPP
#define DAMAGE_SYSTEM_HPP

#include <memory>
#include <string>

#include "../components/circleColliderComponent.hpp"
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
   * @details This is the callback function that is called when a collision
   */
  void onCollision(CollisionEvent& event) {
    DEBUG_MSG("[Game] Collision detected between " +
              std::to_string(event.entityA.getId()) + " and " +
              std::to_string(event.entityB.getId()));

    event.entityA.killEntity();
    event.entityB.killEntity();
  }
};

#endif  // DAMAGE_SYSTEM_HPP