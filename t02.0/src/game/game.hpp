#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <sol/sol.hpp>

#include "../assetManager/assetManager.hpp"
#include "../controllerManager/controllerManager.hpp"
#include "../ecs/ecs.hpp"
#include "../eventManager/eventManager.hpp"
#include "../sceneManager/sceneLoader.hpp"
#include "../sceneManager/sceneManager.hpp"

#define SDL_DEFAULT_SCREEN_DRIVER -1  // Default screen driver index
#define SDL_WITHOUT_FLAGS 0           // No flags for SDL initialization

const int FPS = 60;                      // Frames per second
const int MILLI_PER_FRAME = 1000 / FPS;  // Milliseconds per frame
const double MAX_DELTA_TIME = 0.05;

/**
 * @class Game
 * @brief This class is a singleton that represents the game itself.
 * It has the main loop and the main methods to run the game.
 */
class Game {
 private:                 // attributes
  SDL_Window *window;     // SDL window pointer
  bool isRunning;         // Flag to control the game loop.
  int windowWidth;        // Window width
  int windowHeight;       // Window height
  int miliPreviousFrame;  // Milliseconds per frame (previous frame)
  bool isPaused;          // Flag to control the pause state

 public:
  std::unique_ptr<Register> registry;                    // ECS registry
  std::unique_ptr<AssetManager> assetManager;            // Asset manager
  std::unique_ptr<EventManager> eventManager;            // Event manager
  std::unique_ptr<ControllerManager> controllerManager;  // Controller manager
  std::unique_ptr<SceneManager> sceneManager;            // Scene manager
  SDL_Renderer *renderer;  // SDL renderer pointer+
  sol::state lua;          // Lua state

 private:  // methods
  /**
   * @brief Game constructor
   */
  Game();

  /**
   * @brief Game destructor
   */
  ~Game();

  /**
   * @brief Set up and initialize the game objects, components, systems, and
   * assets.
   */
  void setUp();

  /**
   * @brief Handle the events of the game.
   */
  void handleEvents();

  /**
   * @brief Update the game objects.
   * @details Update the game objects by calling the update method of the
   * Registry
   */
  void update();

  /**
   * @brief Render game objects and window.
   * @details Render the game objects by calling the render method of the
   * systems in the Registry and render the window. And calculates delta time.
   */
  void render();

  /**
   * @brief Run the scene.
   */
  void runScene();

 public:
  /**
   * @brief Get the instance of the Game class.
   * @return Game& The instance of the Game class.
   */
  static Game &getInstance();

  /**
   * @brief Initialize the game.
   */
  void init();

  /**
   * @brief Run the game.
   */
  void run();

  /**
   * @brief Destroy the game.
   * @details Free all the resources used by the game.
   */
  void destroy();

  void togglePause();
};

#endif  // GAME_HPP