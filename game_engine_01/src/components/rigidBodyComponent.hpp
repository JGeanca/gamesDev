#ifndef RIGID_BODY_COMPONENT_HPP
#define RIGID_BODY_COMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct RigidBodyComponent
 * @brief This structure represents the rigid body component of an entity.
 * @details Rigid body represents the physics of an entity.
 */
struct RigidBodyComponent {
  glm::vec2 velocity;  // Velocity of the entity
  // TODO: Add acceleration and mass
  /**
   * @brief RigidBodyComponent constructor
   * @param velocity The velocity of the entity
   */
  RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0))
      : velocity(velocity) {}
};

#endif  // RIGID_BODY_COMPONENT_HPP