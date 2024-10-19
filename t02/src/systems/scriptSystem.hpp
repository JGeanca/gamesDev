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
    lua.set_function("get_velocity", getVelocity);
    lua.set_function("go_to_scene", goToScene);
    lua.set_function("set_text_visibility", setTextVisibility);
    lua.set_function("play_sound", playSound);
    lua.set_function("play_music", playMusic);
    lua.set_function("stop_music", stopMusic);
    lua.set_function("get_tag", getTag);
    lua.set_function("left_collision", leftCollision);
    lua.set_function("right_collision", rightCollision);
    lua.set_function("top_collision", topCollision);
    lua.set_function("bottom_collision", bottomCollision);
    lua.set_function("get_position", getPosition);
    lua.set_function("set_position", setPosition);
    lua.set_function("get_size", getSize);
    lua.set_function("get_collision_type", getCollisionTypeString);
    lua.set_function("kill_entity", killEntity);
    lua.set_function("kill_entity_by_id", killEntityById);
    lua.set_function("create_entity", createEntity);
    lua.set_function("entity_exists", entityExists);
    lua.set_function("entity_exists_by_id", entityExistsById);
    lua.set_function("get_entity_id", getEntityId);
    lua.set_function("create_text_entity", createTextEntity);
  }

  /**
   * @brief This method updates the script components.
   * @param lua The lua state.
   * @param deltaTime The time between frames.
   */
  void update(sol::state& lua, float deltaTime = 0.0f) {
    for (auto& entity : getEntities()) {
      auto& script = entity.getComponent<ScriptComponent>();

      if (!script.initialized) {
        for (auto& initFunction : script.initFunctions) {
          if (initFunction != sol::nil) {
            lua["this"] = entity;
            initFunction();
          }
        }
        script.initialized = true;
      }

      for (auto& updateFunction : script.updateFunctions) {
        if (updateFunction != sol::nil) {
          lua["this"] = entity;
          updateFunction(deltaTime);
        }
      }
    }
  }
};

#endif  // SCRIPT_SYSTEM_HPP