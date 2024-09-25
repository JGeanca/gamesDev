#include "sceneManager.hpp"

#include <iostream>

#include "../game/game.hpp"
#include "../utils/debug.hpp"

SceneManager::SceneManager() {
  DEBUG_MSG("[SceneManager] constructor");
  this->sceneLoader = std::make_unique<SceneLoader>();
}

SceneManager::~SceneManager() { DEBUG_MSG("[SceneManager] destructor"); }

void SceneManager::loadSceneFromScript(const std::string& scriptPath,
                                       sol::state& lua) {
  lua.script_file(scriptPath);
  sol::table scenes = lua["scenes"];
  int index = 0;

  while (true) {
    sol::optional<sol::table> hasScenes = scenes[index];
    if (hasScenes == sol::nullopt) {
      break;
    }

    sol::table scene = scenes[index];
    std::string sceneName = scene["name"];
    std::string scenePath = scene["path"];
    this->scenes.emplace(sceneName, scenePath);

    if (index == 0) {
      this->nextScene = sceneName;
    }

    index++;
  }
}

void SceneManager::loadScene() {
  Game& game = Game::getInstance();
  std::string scenePath = scenes[nextScene];
  sceneLoader->loadScene(scenePath, game.lua, game.renderer, game.assetManager,
                         game.controllerManager, game.registry);
}

void SceneManager::setNextScene(const std::string& nextScene) {
  this->nextScene = nextScene;
}

std::string SceneManager::getNextScene() const { return this->nextScene; }

bool SceneManager::isSceneRunning() const { return isRunning; }

void SceneManager::startScene() { this->isRunning = true; }

void SceneManager::stopScene() { this->isRunning = false; }