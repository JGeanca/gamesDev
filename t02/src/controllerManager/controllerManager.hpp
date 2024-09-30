#ifndef CONTROLLER_MANAGER_HPP
#define CONTROLLER_MANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>
#include <tuple>

/**
 * @class ControllerManager
 * @brief Manages the input from the user
 */
class ControllerManager {
 private:
  std::map<std::string, int> actionKeyName;  // action -> keyCode
  std::map<int, bool> keyDown;               // keyCode -> isKeyDown

  std::map<std::string, int> mouseButtonName;  // action -> mouseButton
  std::map<int, bool> mouseButtonDown;         // mouseButton -> isButtonDown

  int mousePosX;  // mouse position x
  int mousePosY;  // mouse position y

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

  /**
   * @brief Add a mouse button to the action
   * @param name The action to add the mouse button to
   * @param mouseButtonCode The mouse button to add to the action
   */
  void addMouseButton(const std::string& name, int mouseButtonCode);

  /**
   * @brief Handle the mouse button down event
   * @param mouseButtonCode The mouse button code of the button that was pressed
   */
  void mouseButtonDownEvent(int mouseButtonCode);

  /**
   * @brief Handle the mouse button up event
   * @param mouseButtonCode The mouse button code of the button that was
   * released
   */
  void mouseButtonUpEvent(int mouseButtonCode);

  /**
   * @brief Check if the mouse button is down
   * @param name The action to check
   * @return true if the mouse button is down, false otherwise
   */
  bool isMouseButtonDown(const std::string& name);

  /**
   * @brief Set the mouse position
   * @param x The x position of the mouse
   * @param y The y position of the mouse
   */
  void setMousePos(int x, int y);

  /**
   * @brief Get the mouse position
   * @param x The x position of the mouse
   * @param y The y position of the mouse
   * @return A tuple with the x and y position of the mouse
   */
  std::tuple<int, int> getMousePos();
};

#endif  // CONTROLLER_MANAGER_HPP