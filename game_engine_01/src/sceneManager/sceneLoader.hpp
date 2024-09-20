#ifndef SCENE_LOADER_HPP
#define SCENE_LOADER_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "../assetManager/assetManager.hpp"
#include "../controllerManager/controllerManager.hpp"
#include "../ecs/ecs.hpp"

/**
 * @class SceneLoader
 * @brief This class is for loading scenes
 */
class SceneLoader {
 private:
  /**
   * @brief Load the sprites from the lua table
   * @param renderer SDL renderer pointer
   * @param sprites Lua table containing the sprites
   * @param assetManager Asset manager pointer
   */
  void loadSprites(SDL_Renderer* renderer, const sol::table& sprites,
                   std::unique_ptr<AssetManager>& assetManager);

  /**
   * @brief Load the key bindings from the lua table
   * @param keyBindings Lua table containing the key bindings
   * @param controllerManager Controller manager pointer
   */
  void loadKeyBindings(const sol::table& keyBindings,
                       std::unique_ptr<ControllerManager>& controllerManager);

  /**
   * @brief  Load the entities from the lua table
   * @param lua Lua state
   * @param entities Lua table containing the entities
   * @param registry Registry pointer
   */
  void loadEntities(sol::state& lua, sol::table& entities,
                    std::unique_ptr<Register>& registry);

 public:
  /**
   * @brief Construct a new Scene Loader object
   */
  SceneLoader();

  /**
   * @brief Destroy the Scene Loader object
   */
  ~SceneLoader();

  /**
   * @brief Load a scene
   * @param scenePath Path to the scene file
   * @param lua Lua state
   * @param renderer SDL renderer pointer
   * @param assetManager Asset manager pointer
   * @param controllerManager Controller manager pointer
   * @param registry Registry pointer
   */
  void loadScene(const std::string& scenePath, sol::state& lua,
                 SDL_Renderer* renderer,
                 std::unique_ptr<AssetManager>& assetManager,
                 std::unique_ptr<ControllerManager>& controllerManager,
                 std::unique_ptr<Register>& registry);
};

#endif  // SCENE_LOADER_HPP
