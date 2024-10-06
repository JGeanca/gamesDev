#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include <iostream>
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
    lua.set_function("set_text_visibility", setTextVisibility);
    lua.set_function("play_sound", playSound);
    lua.set_function("play_music", playMusic);
    lua.set_function("stop_music", stopMusic);
    lua.set_function("get_tag", getTag);
  }

  /**
   * @brief This method updates the script components.
   * @param lua The lua state.
   */
  void update(sol::state& lua) {
    for (auto& entity : getEntities()) {
      auto& script = entity.getComponent<ScriptComponent>();

      if (!script.initialized) {
        if (script.init != sol::lua_nil) {
          script.init();
        }
        script.initialized = true;
      }

      if (script.update != sol::lua_nil) {
        lua["this"] = entity;
        script.update();
      }
    }
  }
};

#endif  // SCRIPT_SYSTEM_HPP