#include "controllerManager.hpp"

#include "../utils/debug.hpp"
ControllerManager::ControllerManager() {
  DEBUG_MSG("[ControllerManager] created");
}
ControllerManager::~ControllerManager() {
  DEBUG_MSG("[ControllerManager] destroyed");
}

void ControllerManager::addActionKey(const std::string& action, int keyCode) {
  actionKeyName.emplace(action, keyCode);
  keyDown.emplace(keyCode, false);
}
void ControllerManager::keyDownEvent(int keyCode) {
  auto it = keyDown.find(keyCode);
  if (it != keyDown.end()) {
    keyDown[keyCode] = true;
  }
}
void ControllerManager::keyUpEvent(int keyCode) {
  auto it = keyDown.find(keyCode);
  if (it != keyDown.end()) {
    keyDown[keyCode] = false;
  }
}

bool ControllerManager::isActionActivated(const std::string& action) {
  auto it = actionKeyName.find(action);
  if (it != actionKeyName.end()) {
    int actionKeyCode = actionKeyName[action];
    return keyDown[actionKeyCode];
  }
  return false;
}

void ControllerManager::clear() {
  actionKeyName.clear();
  keyDown.clear();
}