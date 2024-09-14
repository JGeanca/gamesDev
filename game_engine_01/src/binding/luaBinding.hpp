#ifndef LUA_BINDING_HPP
#define LUA_BINDING_HPP

#include <string>

#include "../game/game.hpp"

/**
 * @brief Verify if the action is activated.
 * @param action The action to verify.
 * @return true If the action is activated, false otherwise.
 */
bool isActionActivated(const std::string& action) {
  return Game::getInstance().controllerManager->isActionActivated(action);
}

#endif  // LUA_BINDING_HPP