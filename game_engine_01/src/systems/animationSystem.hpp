#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../components/animationComponent.hpp"
#include "../components/spriteComponent.hpp"
#include "../ecs/ecs.hpp"

/**
 * @class AnimationSystem
 * @brief This class is a system
 * that manages the animation components.
 */
class AnimationSystem : public System {
 public:
  /**
   * @brief AnimationSystem constructor.
   */
  AnimationSystem() {
    requireComponent<AnimationComponent>();
    requireComponent<SpriteComponent>();
  }

  /**
   * @brief This method updates the animation components.
   * @details It takes the current time and calculates the current frame of the
   * animation, then updates the source rectangle of the sprite component with
   * the current frame to render the correct frame.
   */
  void update() {
    for (auto& entity : getEntities()) {
      auto& animation = entity.getComponent<AnimationComponent>();
      auto& sprite = entity.getComponent<SpriteComponent>();

      animation.currentFrame = ((SDL_GetTicks() - animation.startTime) *
                                animation.frameSpeedRate / 1000) %
                               animation.numFrames;
      sprite.srcRect.x = sprite.width * animation.currentFrame;
    }
  }
};

#endif  // ANIMATION_SYSTEM_HPP