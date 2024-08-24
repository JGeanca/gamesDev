#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <iostream>

int main(int argc, char* argv[]) {

  glm::vec2 position = {65.0f, 98.0f};

  sol::state lua;
  

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  int screenWidth = 800;
  int screenHeight = 600;

  bool isRunning = true;

  SDL_Rect rect = { 
    (screenWidth/2), // x position
    (screenHeight/2), // y position
    50, // width
    50 // height 
  };

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  window = SDL_CreateWindow(
    "Intro",
    SDL_WINDOWPOS_CENTERED, // x position
    SDL_WINDOWPOS_CENTERED, // y position
    screenWidth, // width
    screenHeight, // height
    SDL_WINDOW_SHOWN // flags
  );

  renderer = SDL_CreateRenderer  (
    window,
   -1, // Driver index screen
    0 // flags; 0 is without flags
  );

  while (isRunning)  {
    // Event handling
    SDL_Event event;

    // Polling for events
    // Get the event from the event queue and store it in the event variable
    while (SDL_PollEvent(&event)) {
      
      switch (event.type) { // Event handling
        case SDL_QUIT: // Equivalent to pressing close button on window
          isRunning = false; 
          break;

        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
            break;
          }

        default:
          break;
      }
    }


    // Set the color of the window
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    // Clear the window to the set color
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw the rectangle
    SDL_RenderFillRect(renderer, &rect);


    // Render the window
    SDL_RenderPresent(renderer);
  }
  

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}