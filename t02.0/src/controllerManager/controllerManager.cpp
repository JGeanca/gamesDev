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

void ControllerManager::addMouseButton(const std::string& name,
                                       int mouseButtonCode) {
  mouseButtonName.emplace(name, mouseButtonCode);
  mouseButtonDown.emplace(mouseButtonCode, false);
}

void ControllerManager::mouseButtonDownEvent(int mouseButtonCode) {
  auto it = mouseButtonDown.find(mouseButtonCode);
  if (it != mouseButtonDown.end()) {
    mouseButtonDown[mouseButtonCode] = true;
  }
}

void ControllerManager::mouseButtonUpEvent(int mouseButtonCode) {
  auto it = mouseButtonDown.find(mouseButtonCode);
  if (it != mouseButtonDown.end()) {
    mouseButtonDown[mouseButtonCode] = false;
  }
}

bool ControllerManager::isMouseButtonDown(const std::string& name) {
  auto it = mouseButtonName.find(name);
  if (it != mouseButtonName.end()) {
    int mouseButtonCode = mouseButtonName[name];
    return mouseButtonDown[mouseButtonCode];
  }
  return false;
}

void ControllerManager::setMousePos(int x, int y) {
  this->mousePosX = x;
  this->mousePosY = y;
}

std::tuple<int, int> ControllerManager::getMousePos() {
  return {this->mousePosX, this->mousePosY};
}
