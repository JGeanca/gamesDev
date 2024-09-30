#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../binding/luaBinding.hpp"
#include "../components/scriptComponent.hpp"
#include "../ecs/ecs.hpp"

/**
 * @class ScriptSystem
 * @brief This class is a system
 * that manages the script components.
 */
class ScriptSystem : public System {
 public:
  /**
   * @brief ScriptSystem constructor.
   */
  ScriptSystem() { requireComponent<ScriptComponent>(); }

  /**
   * @brief this method creates the lua bindings.
   * @param lua The lua state.
   */
  void createLuaBinding(sol::state& lua) {
    // classes
    lua.new_usertype<Entity>("entity");

    // functions
    lua.set_function("is_action_activated", isActionActivated);
    lua.set_function("set_velocity", setVelocity);
    lua.set_function("go_to_scene", goToScene);
  }

  /**
   * @brief This method updates the script components.
   * @param lua The lua state.
   */
  void update(sol::state& lua) {
    for (auto& entity : getEntities()) {
      const auto& script = entity.getComponent<ScriptComponent>();
      if (script.update != sol::lua_nil) {
        lua["this"] = entity;
        script.update();
      }
    }
  }
};

#endif  // SCRIPT_SYSTEM_HPP