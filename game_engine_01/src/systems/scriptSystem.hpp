#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../binding/luaBinding.hpp"
#include "../components/scriptComponent.hpp"
#include "../ecs/ecs.hpp"

class ScriptSystem : public System {
 public:
  ScriptSystem() { requireComponent<ScriptComponent>(); }

  void createLuaBinding(sol::state& lua) {
    lua.set_function("is_action_activated", isActionActivated);
  }

  void update(sol::state& lua) {
    for (auto& entity : getEntities()) {
      const auto& script = entity.getComponent<ScriptComponent>();
      script.update();

      if (script.update != sol::lua_nil) {
        script.update();
      }
    }
  }
};

#endif  // SCRIPT_SYSTEM_HPP