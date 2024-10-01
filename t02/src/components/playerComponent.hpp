#ifndef PLAYER_COMPONENT_HPP
#define PLAYER_COMPONENT_HPP

#include <glm/glm.hpp>

/**
 * @struct PlayerComponent
 * @brief Define the player component
 */
struct PlayerComponent {
  glm::vec2 resetPosition;
  /**
   * @brief Construct a new Player Component object
   */
  PlayerComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0))
      : resetPosition(velocity) {}
};

#endif  // PLAYER_COMPONENT_HPP