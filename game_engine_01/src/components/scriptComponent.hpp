#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @struct ScriptComponent
 * @brief A component that holds a scripts functions in Lua
 */
struct ScriptComponent {
  sol::function update;   // sol function to be called every frame
  sol::function onClick;  // sol function to be called when clicked

  /**
   * @brief Construct a new Script Component object
   * @param update The update function
   * @param onClick The onClick function
   */
  ScriptComponent(sol::function update = sol::lua_nil,
                  sol::function onClick = sol::lua_nil)
      : update(update), onClick(onClick) {}
};

#endif  // SCRIPT_COMPONENT_HPP