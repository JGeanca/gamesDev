#ifndef HEALTH_SYSTEM_HPP
#define HEALTH_SYSTEM_HPP

#include "../components/healthComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../utils/debug.hpp"

class HealthSystem : public System {
 public:
  HealthSystem() { requireComponent<HealthComponent>(); }

  void update(double deltaTime) {
    for (auto entity : getEntities()) {
      auto& health = entity.getComponent<HealthComponent>();

      // Handle regeneration
      if (health.regenerationRate > 0) {
        health.regenerationTimer += deltaTime;
        if (health.regenerationTimer >= 1.0 &&
            health.currentHealth < health.maxHealth) {
          health.regenerationTimer = 0;
          health.heal(health.regenerationRate);
          DEBUG_MSG("Entity " + std::to_string(entity.getId()) +
                    " regenerated " + std::to_string(health.regenerationRate) +
                    " health points");
        }
      }
    }
  }
};

#endif  // HEALTH_SYSTEM_HPP