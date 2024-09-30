#ifndef CIRCLE_COLLIDER_COMPONENT_HPP
#define CIRCLE_COLLIDER_COMPONENT_HPP

/**
 * @struct circleColliderComponent
 * @brief Define a circle collider to an entity (the hitBox)
 */
struct CircleColliderComponent {
  int radius;  // Radius of the circle collider
  int width;   // Width of the circle collider
  int height;  // Height of the circle collider

  /**
   * @brief Constructor
   * @param radius Radius of the circle collider
   * @param width Width of the circle collider
   * @param height Height of the circle collider
   */
  CircleColliderComponent(int radius = 0, int width = 0, int height = 0)
      : radius(radius), width(width), height(height) {}
};

#endif  // CIRCLE_COLLIDER_COMPONENT_HPP