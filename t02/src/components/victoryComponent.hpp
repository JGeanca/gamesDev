#ifndef VICTORY_COMPONENT_HPP
#define VICTORY_COMPONENT_HPP

#include <string>

/**
 * @struct VictoryComponent
 * @brief This structure represents the victory component of the game.
 * @details Victory component is responsible for storing the next level to load
 * when the player wins the game.
 */
struct VictoryComponent {
  std::string nextLevel;  // Next level scene to load

  /**
   * @brief Construct a new Victory Component object
   */
  VictoryComponent(const std::string& nextLevel = "") : nextLevel(nextLevel) {}
};

#endif  // VICTORY_COMPONENT_HPP