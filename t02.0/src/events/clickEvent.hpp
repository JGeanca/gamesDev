#ifndef CLICK_EVENT_HPP
#define CLICK_EVENT_HPP

#include "../ecs/ecs.hpp"
#include "../eventManager/event.hpp"

/**
 * @class ClickEvent
 * @brief Event for mouse click
 */
class ClickEvent : public Event {
 public:
  int buttonCode;  // The button code of the mouse
  int posX;        // The x position of the mouse
  int posY;        // The y position of the mouse

  /**
   * @brief Constructor
   * @param buttonCode The button code of the mouse
   * @param posX The x position of the mouse
   * @param posY The y position of the mouse
   */
  ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0)
      : buttonCode(buttonCode), posX(posX), posY(posY) {}
};

#endif  // CLICK_EVENT_HPP