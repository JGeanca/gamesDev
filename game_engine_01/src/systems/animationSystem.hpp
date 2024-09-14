#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../components/animationComponent.hpp"
#include "../components/spriteComponent.hpp"
#include "../ecs/ecs.hpp"

class AnimationSystem : public System {
 public:
  AnimationSystem() {
    requireComponent<AnimationComponent>();
    requireComponent<SpriteComponent>();
  }

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