#ifndef COLLISION_EVENT_HPP
#define COLLISION_EVENT_HPP

#include "../ecs/ecs.hpp"
#include "../eventManager/event.hpp"

/**
 * @class CollisionEvent
 * @brief Event for collision between two entities
 */
class CollisionEvent : public Event {
 public:
  Entity entityA;  // Entity A in the collision
  Entity entityB;  // Entity B in the collision

  /**
   * @brief Constructor
   * @param entityA Entity A in the collision
   * @param entityB Entity B in the collision
   */
  CollisionEvent(Entity entityA, Entity entityB)
      : entityA(entityA), entityB(entityB) {}
};

#endif  // COLLISION_EVENT_HPP