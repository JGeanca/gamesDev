#ifndef SCENE_LOADER_HPP
#define SCENE_LOADER_HPP

#include <SDL2/SDL.h>
#include <tinyxml2/tinyxml2.h>

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

  void loadMap(const sol::table& map, std::unique_ptr<Register>& registry);
  void loadLayer(std::unique_ptr<Register>& registry,
                 tinyxml2::XMLElement* layer, int tWidth, int tHeight,
                 int mWidth, const std::string& tileSet, int columns);

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

  /**
   * @brief Add a tag component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addTagComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add an animation component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addAnimationComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a circle collider component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addCircleColliderComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a box collider component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addBoxColliderComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a rigid body component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addRigidBodyComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a sprite component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addSpriteComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a text component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addTextComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a clickable component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addClickableComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a transform component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addTransformComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a script component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   * @param lua Lua state
   */
  void addScriptComponent(Entity& entity, const sol::table& components,
                          sol::state& lua);

  /** @brief Add a health component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addHealthComponent(Entity& entity, const sol::table& components);

  /**
   * @brief Add a camera follow component to an entity
   * @param entity Entity to add the component to
   * @param components Lua table containing the component data
   */
  void addCameraFollowComponent(Entity& entity, const sol::table& components);
};

#endif  // SCENE_LOADER_HPP
