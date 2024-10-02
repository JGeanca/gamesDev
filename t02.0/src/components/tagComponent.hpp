#ifndef TAG_COMPONENT_HPP
#define TAG_COMPONENT_HPP

#include <string>

/**
 * @struct TagComponent
 * @brief This struct represents the tag component of an entity.
 * @details The tag component is used to identify the entity.
 */
struct TagComponent {
  std::string tag;

  TagComponent() = default;
  explicit TagComponent(const std::string& tag) : tag(tag) {}
};

#endif  // TAG_COMPONENT_HPP