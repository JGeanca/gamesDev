#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>


#define SDL_DEFAULT_SCREEN_DRIVER -1
#define SDL_WITHOUT_FLAGS 0

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;
class Game {
  
  private: // attributes
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    int miliPreviousFrame = 0;

    size_t screenWidth = 800;
    size_t screenHeight = 600;
    bool running;

    // Image attributes
    SDL_Texture* imgTexture = nullptr;
    glm::vec2 position = glm::vec2();
    glm::vec2 imgVel = glm::vec2();

    size_t imgWidth = 0;
    size_t imgHeight = 0;
    SDL_Rect srcRect= {0, 0, 0, 0};
    double angle = 0.0;
    

    // Text attributes
    TTF_Font* font = nullptr;
    int fontSize = 0;
    SDL_Color fontColor = {0, 0, 0, 0};
    SDL_Texture* textTexture = nullptr;
    std::string text = "";
    glm::vec2 textPosition = glm::vec2();
    size_t txtWidth = 0;
    size_t txtHeight = 0;
    double txtAngle = 0.0;


  private: // methods
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
