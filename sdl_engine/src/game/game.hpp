#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <iostream>

#define SDL_DEFAULT_SCREEN_DRIVER -1
#define SDL_WITHOUT_FLAGS 0

class Game {
  private:
    // attributes
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    size_t screenWidth = 600;
    size_t screenHeight = 400;
    bool running;

    // methods
    void handleEvents();
    void update();
    void render();
  public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
    inline bool isRunning() const { return running; }
};

#endif
