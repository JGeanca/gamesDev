#ifndef UI_SYSTEM_HPP
#define UI_SYSTEM_HPP

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <string>

#include "../components/clickableComponent.hpp"
#include "../components/scriptComponent.hpp"
#include "../components/textComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../eventManager/eventManager.hpp"
#include "../events/clickEvent.hpp"

/**
 * @class UISystem
 * @brief This class is for handling the UI
 */
class UISystem : public System {
 public:
  /**
   * @brief Construct a new UISystem object
   */
  UISystem() {
    requireComponent<TransformComponent>();
    requireComponent<TextComponent>();
    requireComponent<ClickableComponent>();
  }

  /**
   * @brief Subscribe to click events
   * @param eventManager The event manager
   */
  void subscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
    eventManager->subscribeToEvent<ClickEvent, UISystem>(
        this, &UISystem::onClickEvent);
  }

  void onClickEvent(ClickEvent& event) {
    for (auto entity : getEntities()) {
      auto& transform = entity.getComponent<TransformComponent>();
      auto& text = entity.getComponent<TextComponent>();

      if (transform.position.x < event.posX &&
          event.posX < transform.position.x + text.width &&
          event.posY > transform.position.y &&
          event.posY < transform.position.y + text.height) {
        if (entity.hasComponent<ScriptComponent>()) {
          auto& script = entity.getComponent<ScriptComponent>();
          for (auto& onClickFunction : script.onClickFunctions) {
            if (onClickFunction != sol::nil) {
              onClickFunction();
            }
          }
        }
      }
    }
  }
};

#endif  // UI_SYSTEM_HPP