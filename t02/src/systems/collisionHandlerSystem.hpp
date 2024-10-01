#ifndef COLLISION_HANDLER_SYSTEM_HPP
#define COLLISION_HANDLER_SYSTEM_HPP

#include <memory>
#include <string>

#include "../components/circleColliderComponent.hpp"
#include "../components/enemyComponent.hpp"
#include "../components/playerComponent.hpp"
#include "../components/victoryComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../eventManager/eventManager.hpp"
#include "../events/collisionEvent.hpp"
#include "../game/game.hpp"
#include "../utils/debug.hpp"

class CollisionHandlerSystem : public System {
 public:
  /**
   * @brief CollisionHandlerSystem constructor
   * @details This constructor requires the CircleColliderComponent to be
   * present in the entity. **Requires means that the entity must have this
   * component to be processed by the system.
   */
  CollisionHandlerSystem() { requireComponent<CircleColliderComponent>(); }

  /**
   * @brief Suscribe the system (CollisionHandlerSystem) to the collision event
   * @param eventManager Event manager
   */
  void suscribeToCollisionEvent(std::unique_ptr<EventManager>& eventManager) {
    eventManager->subscribeToEvent<CollisionEvent, CollisionHandlerSystem>(
        this, &CollisionHandlerSystem::onCollision);
  }

  bool isPlayerEnemyCollision(Entity& entityA, Entity& entityB) {
    return (entityA.hasComponent<PlayerComponent>() &&
            entityB.hasComponent<EnemyComponent>()) ||
           (entityA.hasComponent<EnemyComponent>() &&
            entityB.hasComponent<PlayerComponent>());
  }

  bool isPlayerVictoryCollision(Entity& entityA, Entity& entityB) {
    return (entityA.hasComponent<PlayerComponent>() &&
            entityB.hasComponent<VictoryComponent>()) ||
           (entityA.hasComponent<VictoryComponent>() &&
            entityB.hasComponent<PlayerComponent>());
  }

  void onCollision(CollisionEvent& event) {
    DEBUG_MSG("[DamageSystem] Collision detected between " +
              std::to_string(event.entityA.getId()) + " and " +
              std::to_string(event.entityB.getId()));
    handlePlayerEnemyCollision(event.entityA, event.entityB);
    handlePlayerVictoryCollision(event.entityA, event.entityB);
  }

  void handlePlayerEnemyCollision(Entity& entityA, Entity& entityB) {
    if (isPlayerEnemyCollision(entityA, entityB)) {
      Entity& player =
          entityA.hasComponent<PlayerComponent>() ? entityA : entityB;
      DEBUG_MSG("[Game] Player collided with enemy. Player ID: " +
                std::to_string(player.getId()));
      player.killEntity();
    }
  }

  void handlePlayerVictoryCollision(Entity& entityA, Entity& entityB) {
    if (isPlayerVictoryCollision(entityA, entityB)) {
      Entity& victory =
          entityA.hasComponent<VictoryComponent>() ? entityA : entityB;
      DEBUG_MSG("[Game] Player has reached the victory point. Next level: " +
                victory.getComponent<VictoryComponent>().nextLevel);

      Game& game = Game::getInstance();
      game.sceneManager->setNextScene(
          victory.getComponent<VictoryComponent>().nextLevel);
      game.sceneManager->stopScene();
    }
  }
};

#endif  // COLLISION_HANDLER_SYSTEM_HPP