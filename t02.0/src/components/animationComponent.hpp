#ifndef ANIMATION_COMPONENT_HPP
#define ANIMATION_COMPONENT_HPP

#include <SDL2/SDL.h>

/**
 * @struct AnimationComponent
 * @brief This structure represents the animation component of the game.
 * @details Animation component is responsible for storing the animation data of
 * an entity.
 */
struct AnimationComponent {
  int numFrames;       // Number of frames in the animation needed to loop
  int currentFrame;    // Current frame of the animation
  int frameSpeedRate;  // Time to show each frame
  int startTime;       // Time to start the animation
  bool isLoop;         // Flag to indicate if the animation should loop

  /**
   * @brief AnimationComponent constructor
   * @param numFrames Number of frames in the animation needed to loop
   * @param frameSpeedRate Time to show each frame
   * @param startTime Time to start the animation
   * @param isLoop Flag to indicate if the animation should loop
   */
  AnimationComponent(int numFrames = 1, int frameSpeedRate = 1,
                     bool isLoop = true)
      : numFrames(numFrames),
        currentFrame(1),
        frameSpeedRate(frameSpeedRate),
        startTime(SDL_GetTicks()),
        isLoop(isLoop) {}
};

#endif  // ANIMATION_COMPONENT_HPP