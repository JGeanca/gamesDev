#include "game.hpp"

#include <iostream>

#include "../controllerManager/controllerManager.hpp"
#include "../events/clickEvent.hpp"
#include "../sceneManager/sceneManager.hpp"
#include "../systems/animationSystem.hpp"
#include "../systems/collisionSystem.hpp"
#include "../systems/damageSystem.hpp"
#include "../systems/healthSystem.hpp"
#include "../systems/movementSystem.hpp"
#include "../systems/renderSystem.hpp"
#include "../systems/renderTextSystem.hpp"
#include "../systems/scriptSystem.hpp"
#include "../systems/uiSystem.hpp"
#include "../utils/debug.hpp"

Game::Game() {
  DEBUG_MSG("[Game] Game constructor called");
  this->isPaused = false;
  this->window = nullptr;
  this->renderer = nullptr;
  this->isRunning = false;
  this->miliPreviousFrame = 0;
  this->registry = std::make_unique<Register>();
  this->assetManager = std::make_unique<AssetManager>();
  this->eventManager = std::make_unique<EventManager>();
  this->controllerManager = std::make_unique<ControllerManager>();
  this->sceneManager = std::make_unique<SceneManager>();
  init();
}

Game::~Game() {
  DEBUG_MSG("[Game] Game destructor called");
  destroy();
  this->assetManager.reset();
  this->controllerManager.reset();
  this->eventManager.reset();
  this->registry.reset();
  this->sceneManager.reset();
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
  registry->addSystem<HealthSystem>();

  sceneManager->loadSceneFromScript("./assets/scripts/scenes.lua", lua);

  lua.open_libraries(sol::lib::base, sol::lib::math);
  registry->getSystem<ScriptSystem>().createLuaBinding(lua);
}

void Game::runScene() {
  sceneManager->loadScene();
  while (sceneManager->isSceneRunning()) {
    handleEvents();
    update();
    render();
  }
  assetManager->clearAssets();
  registry->clearAllEntities();
}

void Game::run() {
  setUp();
  this->isRunning = true;
  while (isRunning) {
    sceneManager->startScene();
    runScene();
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

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        sceneManager->stopScene();
        this->isRunning = false;
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          sceneManager->stopScene();
          this->isRunning = false;
          break;
        }
        if (event.key.keysym.sym == SDLK_p) {
          togglePause();
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
        controllerManager->mouseButtonDownEvent(
            static_cast<int>(event.button.button));
        eventManager->emitEvent<ClickEvent>(event.button.button, event.button.x,
                                            event.button.y);
        break;
      case SDL_MOUSEBUTTONUP:
        controllerManager->setMousePos(event.button.x, event.button.y);
        controllerManager->mouseButtonUpEvent(
            static_cast<int>(event.button.button));
        break;
      default:
        break;
    }
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
  int timeToWait = MILLI_PER_FRAME - (SDL_GetTicks() - miliPreviousFrame);

  if (0 < timeToWait && timeToWait <= MILLI_PER_FRAME) {
    SDL_Delay(timeToWait);
  }

  double deltaTime = (SDL_GetTicks() - miliPreviousFrame) / 1000.0;

  miliPreviousFrame = SDL_GetTicks();

  // TODO: Add deltaTime to LUA
  if (!isPaused) {
    eventManager->reset();
    registry->getSystem<DamageSystem>().suscribeToCollisionEvent(eventManager);

    registry->update();
    registry->getSystem<MovementSystem>().update(deltaTime);
    registry->getSystem<HealthSystem>().update(deltaTime);
    registry->getSystem<CollisionSystem>().update(eventManager);
    registry->getSystem<AnimationSystem>().update();
  }
  registry->getSystem<ScriptSystem>().update(lua);
  registry->getSystem<UISystem>().subscribeToClickEvent(eventManager);
}

void Game::togglePause() {
  isPaused = !isPaused;
  if (isPaused) {
    DEBUG_MSG("[Game] Game paused");
  } else {
    DEBUG_MSG("[Game] Game resumed");
  }
  lua["scene"]["is_paused"] = isPaused;
}