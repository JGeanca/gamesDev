#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct TransformComponent
 * @brief This structure represents the transform component of an entity.
 * @details Transform a component that represents the position, scale, and
 * rotation of an entity.
 */
struct TransformComponent {
  glm::vec2 position;          // Position of the entity
  glm::vec2 scale;             // Scale of the entity
  glm::vec2 previousPosition;  // Previous position of the entity
  double rotation;             // Rotation of the entity

  /**
   * @brief TransformComponent constructor
   * @param position The position of the entity
   * @param scale The scale of the entity
   * @param rotation The rotation of the entity
   */
  TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                     glm::vec2 scale = glm::vec2(1.0, 1.0),
                     double rotation = 0.0)
      : position(position),
        scale(scale),
        previousPosition(position),
        rotation(rotation) {}
};
#endif  // TRANSFORM_COMPONENT_HPP