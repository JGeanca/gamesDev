#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>

/**
 * @class ControllerManager
 * @brief Manages the input from the user
 */
class ControllerManager {
 private:
  std::map<std::string, int> actionKeyName;  // action -> keyCode
  std::map<int, bool> keyDown;               // keyCode -> isKeyDown

 public:
  /**
   * @brief Construct a new Controller Manager object
   */
  ControllerManager();

  /**
   * @brief Destroy the Controller Manager object
   */
  ~ControllerManager();

  /**
   * @brief Add a key to the action
   * @param action The action to add the key to
   * @param keyCode The key code to add to the action
   */
  void addActionKey(const std::string& action, int keyCode);

  /**
   * @brief Handle the key down event
   * @param keyCode The key code of the key that was pressed
   */
  void keyDownEvent(int keyCode);

  /**
   * @brief Handle the key up event
   * @param keyCode The key code of the key that was released
   */
  void keyUpEvent(int keyCode);

  /**
   * @brief Check if the action is activated
   * @param action The action to check
   * @return true if the action is activated, false otherwise
   */
  bool isActionActivated(const std::string& action);

  /**
   * @brief Clear the actionKeyName and keyDown maps
   */
  void clear();
};

#endif  // CONTROLLER_MANAGER_HPP