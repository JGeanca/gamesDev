#ifndef SCRIPT_COMPONENT_HPP
#define SCRIPT_COMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @struct ScriptComponent
 * @brief A component that holds a scripts functions in Lua
 */
struct ScriptComponent {
  sol::function update;       // sol function to be called every frame
  sol::function onClick;      // sol function to be called when clicked
  sol::function init;         // sol function to be called when initialized
  sol::function onCollision;  // sol function when a collision occurs
  bool initialized;           // flag to check if the script was initialized

  /**
   * @brief Construct a new Script Component object
   * @param update The update function
   * @param onClick The onClick function
   * @param init The init function
   * @param onCollision The onCollision function
   */
  ScriptComponent(sol::function update = sol::lua_nil,
                  sol::function onClick = sol::lua_nil,
                  sol::function init = sol::lua_nil,
                  sol::function onCollision = sol::lua_nil)
      : update(update),
        onClick(onClick),
        init(init),
        onCollision(onCollision),
        initialized(false) {}
};

#endif  // SCRIPT_COMPONENT_HPP