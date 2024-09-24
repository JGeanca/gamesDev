#include "game.hpp"

#include <iostream>

#include "../components/animationComponent.hpp"
#include "../components/circleColliderComponent.hpp"
#include "../components/rigidBodyComponent.hpp"
#include "../components/scriptComponent.hpp"
#include "../components/spriteComponent.hpp"
#include "../components/textComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../controllerManager/controllerManager.hpp"
#include "../events/clickEvent.hpp"
#include "../systems/animationSystem.hpp"
#include "../systems/collisionSystem.hpp"
#include "../systems/damageSystem.hpp"
#include "../systems/movementSystem.hpp"
#include "../systems/renderSystem.hpp"
#include "../systems/renderTextSystem.hpp"
#include "../systems/scriptSystem.hpp"
#include "../systems/uiSystem.hpp"
#include "../utils/debug.hpp"

Game::Game() {
  DEBUG_MSG("[Game] Game constructor called");
  this->window = nullptr;
  this->renderer = nullptr;
  this->isRunning = false;
  this->miliPreviousFrame = 0;
  this->registry = std::make_unique<Register>();
  this->assetManager = std::make_unique<AssetManager>();
  this->eventManager = std::make_unique<EventManager>();
  this->controllerManager = std::make_unique<ControllerManager>();

  this->sceneLoader = std::make_unique<SceneLoader>();

  init();
}

Game::~Game() {
  DEBUG_MSG("[Game] Game destructor called");
  destroy();
  this->assetManager.reset();
  this->controllerManager.reset();
  this->eventManager.reset();
  this->sceneLoader.reset();
  this->registry.reset();
}

Game &Game::getInstance() {
  static Game instance;
  return instance;
}

void Game::init() {
  this->windowWidth = 800;
  this->windowHeight = 600;
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return;
  }

  if (TTF_Init() != 0) {
    std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    return;
  }

  this->window = SDL_CreateWindow("Game Engine 01", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, windowWidth,
                                  windowHeight, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    return;
  }

  this->renderer = SDL_CreateRenderer(this->window, SDL_DEFAULT_SCREEN_DRIVER,
                                      SDL_WITHOUT_FLAGS);
}

void Game::setUp() {
  registry->addSystem<RenderSystem>();
  registry->addSystem<RenderTextSystem>();
  registry->addSystem<MovementSystem>();
  registry->addSystem<AnimationSystem>();
  registry->addSystem<CollisionSystem>();
  registry->addSystem<DamageSystem>();
  registry->addSystem<ScriptSystem>();
  registry->addSystem<UISystem>();

  lua.open_libraries(sol::lib::base, sol::lib::math);
  registry->getSystem<ScriptSystem>().createLuaBinding(lua);

  sceneLoader->loadScene("assets/scripts/scene_01.lua", lua, this->renderer,
                         this->assetManager, this->controllerManager,
                         this->registry);
}

void Game::run() {
  setUp();
  this->isRunning = true;
  while (isRunning) {
    handleEvents();
    update();
    render();
  }
}

void Game::destroy() {
  DEBUG_MSG("[Game] Destroying game");
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  TTF_Quit();
  SDL_Quit();
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      this->isRunning = false;
      break;

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        this->isRunning = false;
        break;
      }
      controllerManager->keyDownEvent(event.key.keysym.sym);
      break;

    case SDL_KEYUP:
      controllerManager->keyUpEvent(event.key.keysym.sym);
      break;
    case SDL_MOUSEMOTION:
      int x, y;
      SDL_GetMouseState(&x, &y);
      controllerManager->setMousePos(x, y);
      break;
    case SDL_MOUSEBUTTONDOWN:
      controllerManager->setMousePos(event.button.x, event.button.y);
      controllerManager->mouseButtonDownEvent(event.button.button);
      eventManager->emitEvent<ClickEvent>(event.button.button, event.button.x,
                                          event.button.y);
      break;
    case SDL_MOUSEBUTTONUP:
      controllerManager->setMousePos(event.button.x, event.button.y);
      controllerManager->mouseButtonUpEvent(event.button.button);
      break;
    default:
      break;
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(this->renderer, 31, 31, 31, 255);
  SDL_RenderClear(this->renderer);

  registry->getSystem<RenderSystem>().update(this->renderer,
                                             this->assetManager);
  registry->getSystem<RenderTextSystem>().update(this->renderer,
                                                 this->assetManager);
  SDL_RenderPresent(this->renderer);
}

void Game::update() {
  Uint32 miliCurrentFrame = SDL_GetTicks();

  // Time between the current frame and the previous frame in seconds
  // used to calculate the movement of the entities in function of the time
  double deltaTime = (miliCurrentFrame - this->miliPreviousFrame) / 1000.0;

  // Limit the maximum deltaTime to avoid large jumps
  if (deltaTime > MAX_DELTA_TIME) {
    deltaTime = MAX_DELTA_TIME;
  }
  // TODO: Add deltaTime to LUA

  // Update the previous frame time
  this->miliPreviousFrame = miliCurrentFrame;

  // The time it took to render the frame
  Uint32 frameTime = SDL_GetTicks() - miliCurrentFrame;

  // Check if the rendering frame time was less than the frame delay
  if (frameTime < MILLI_PER_FRAME) {  // if it was, wait the remaining time
    SDL_Delay(MILLI_PER_FRAME - frameTime);
  }

  eventManager->reset();
  registry->getSystem<DamageSystem>().suscribeToCollisionEvent(eventManager);
  registry->getSystem<UISystem>().subscribeToClickEvent(eventManager);
  registry->update();
  registry->getSystem<ScriptSystem>().update(lua);
  registry->getSystem<MovementSystem>().update(deltaTime);
  registry->getSystem<CollisionSystem>().update(eventManager);
  registry->getSystem<AnimationSystem>().update();
}