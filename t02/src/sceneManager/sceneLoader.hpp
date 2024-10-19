#ifndef SCENE_LOADER_HPP
#define SCENE_LOADER_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "../assetManager/assetManager.hpp"
#include "../audioManager/audioManager.hpp"
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
   * @brief Load the fonts from the lua table
   * @param fonts Lua table containing the fonts
   * @param assetManager Asset manager pointer
   */
  void loadFonts(const sol::table& fonts,
                 std::unique_ptr<AssetManager>& assetManager);

  /**
   * @brief Load the sounds from the lua table
   * @param sounds Lua table containing the sounds
   * @param audioManager Audio manager pointer
   */
  void loadSounds(const sol::table& sounds,
                  std::unique_ptr<AudioManager>& audioManager);

  /**
   * @brief Load the key bindings from the lua table
   * @param keyBindings Lua table containing the key bindings
   * @param controllerManager Controller manager pointer
   */
  void loadKeyBindings(const sol::table& keyBindings,
                       std::unique_ptr<ControllerManager>& controllerManager);

  void loadMouseBindings(const sol::table& mouseBindings,
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
   * @param audioManager Audio manager pointer
   * @param registry Registry pointer
   */
  void loadScene(const std::string& scenePath, sol::state& lua,
                 SDL_Renderer* renderer,
                 std::unique_ptr<AssetManager>& assetManager,
                 std::unique_ptr<ControllerManager>& controllerManager,
                 std::unique_ptr<AudioManager>& audioManager,
                 std::unique_ptr<Register>& registry);

 private:
  // Add component methods
  void addTagComponent(Entity& entity, const sol::table& components);
  void addAnimationComponent(Entity& entity, const sol::table& components);
  void addCircleColliderComponent(Entity& entity, const sol::table& components);
  void addBoxColliderComponent(Entity& entity, const sol::table& components);
  void addRigidBodyComponent(Entity& entity, const sol::table& components);
  void addSpriteComponent(Entity& entity, const sol::table& components);
  void addTextComponent(Entity& entity, const sol::table& components);
  void addClickableComponent(Entity& entity, const sol::table& components);
  void addTransformComponent(Entity& entity, const sol::table& components);
  void addScriptComponent(Entity& entity, const sol::table& components,
                          sol::state& lua);
  void addHealthComponent(Entity& entity, const sol::table& components);
  void addCameraFollowComponent(Entity& entity, const sol::table& components);
};

#endif  // SCENE_LOADER_HPP
