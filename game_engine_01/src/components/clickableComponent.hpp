#ifndef CLICKABLE_COMPONENT_HPP
#define CLICKABLE_COMPONENT_HPP

/**
 * @struct ClickableComponent
 * @brief The component that contains the clickable information
 */
struct ClickableComponent {
  bool isClicked = false;  // Flag to check if the entity is clicked

  /**
   * @brief Construct a new Clickable Component object
   */
  ClickableComponent() { isClicked = false; }
};

#endif  // CLICKABLE_COMPONENT_HPP