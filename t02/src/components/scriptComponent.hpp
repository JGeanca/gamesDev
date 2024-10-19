#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp>
#include <vector>

/**
 * @struct ScriptComponent
 * @brief A component that holds a scripts functions in Lua
 */
struct ScriptComponent {
  std::vector<sol::function> updateFunctions;
  std::vector<sol::function> onClickFunctions;
  std::vector<sol::function> initFunctions;
  std::vector<sol::function> onCollisionFunctions;
  bool initialized;  // flag to check if the script was initialized

  /**
   * @brief Construct a new Script Component object
   * @param update The update function
   * @param onClick The onClick function
   * @param init The init function
   * @param onCollision The onCollision function
   */
  ScriptComponent() : initialized(false) {}
};

#endif  // SCRIPT_COMPONENT_HPP