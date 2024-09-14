#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @struct ScriptComponent
 * @brief A component that holds a scripts functions in Lua
 */
struct ScriptComponent {
  sol::function update;  // sol function to be called every frame

  /**
   * @brief Construct a new Script Component object
   * @param update The update function
   */
  ScriptComponent(sol::function update = sol::lua_nil) : update(update) {}
};

#endif  // SCRIPT_COMPONENT_HPP