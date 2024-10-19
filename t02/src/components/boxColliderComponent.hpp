#ifndef BOX_COLLIDER_COMPONENT_HPP
#define BOX_COLLIDER_COMPONENT_HPP

#include <glm/glm.hpp>

struct BoxColliderComponent {
  int width;         // Width of the collider.
  int height;        // Height of the collider.
  glm::vec2 offset;  // Offset of the collider.

  /**
   * @brief BoxColliderComponent constructor.
   * @param width Width of the collider.
   * @param height Height of the collider.
   * @param offset Offset of the collider.
   */

  BoxColliderComponent(int width = 0, int height = 0,
                       glm::vec2 offset = glm::vec2(0, 0))
      : width(width), height(height), offset(offset) {}
};

#endif  // BOX_COLLIDER_COMPONENT_HPP