#include "sceneLoader.hpp"

#include <glm/glm.hpp>
#include <iostream>

#include "../components/animationComponent.hpp"
#include "../components/circleColliderComponent.hpp"
#include "../components/rigidBodyComponent.hpp"
#include "../components/scriptComponent.hpp"
#include "../components/spriteComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../utils/debug.hpp"

SceneLoader::SceneLoader() { DEBUG_MSG("[SceneLoader] SceneLoader created"); }

SceneLoader::~SceneLoader() {
  DEBUG_MSG("[SceneLoader] SceneLoader destroyed");
}

void SceneLoader::loadSprites(SDL_Renderer* renderer, const sol::table& sprites,
                              std::unique_ptr<AssetManager>& assetManager) {
  int index = 0;

  while (true) {
    sol::optional<sol::table> hasSprite = sprites[index];
    if (hasSprite == sol::nullopt) {
      break;
    }
    sol::table sprite = sprites[index];

    std::string id = sprite["assetId"];
    std::string path = sprite["filePath"];
    std::cout << "id: " << id << " path: " << path << std::endl;
    assetManager->addTexture(renderer, id, path);

    index++;
  }
}

void SceneLoader::loadKeyBindings(
    const sol::table& keyBindings,
    std::unique_ptr<ControllerManager>& controllerManager) {
  int index = 0;

  while (true) {
    sol::optional<sol::table> hasKeys = keyBindings[index];
    if (hasKeys == sol::nullopt) {
      break;
    }
    sol::table key = keyBindings[index];

    std::string name = key["name"];
    int keyCode = key["key"];

    controllerManager->addActionKey(name, keyCode);

    index++;
  }
}

void SceneLoader::loadEntities(sol::state& lua, sol::table& entities,
                               std::unique_ptr<Register>& registry) {
  int index = 0;
  while (true) {
    sol::optional<sol::table> hasEntities = entities[index];
    if (hasEntities == sol::nullopt) {
      break;
    }
    sol::table entity = entities[index];

    Entity newEntity = registry->createEntity();

    sol::optional<sol::table> hasComponents = entity["components"];
    if (hasComponents != sol::nullopt) {
      sol::table components = entity["components"];

      //* AnimateComponent

      //* ColliderComponent
      sol::optional<sol::table> hasColliderComponent =
          components["circle_collider"];
      if (hasColliderComponent != sol::nullopt) {
        newEntity.addComponent<CircleColliderComponent>(
            components["circle_collider"]["radius"],
            components["circle_collider"]["width"],
            components["circle_collider"]["height"]);
      }

      //* RigidBodyComponent
      sol::optional<sol::table> hasRigidBodyComponent = components["rg_body"];

      if (hasRigidBodyComponent != sol::nullopt) {
        newEntity.addComponent<RigidBodyComponent>(
            glm::vec2(components["rg_body"]["velocity"]["x"],
                      components["rg_body"]["velocity"]["y"]));
      }

      //* SpriteComponent
      sol::optional<sol::table> hasSpriteComponent = components["sprite"];
      if (hasSpriteComponent != sol::nullopt) {
        newEntity.addComponent<SpriteComponent>(
            components["sprite"]["assetId"], components["sprite"]["width"],
            components["sprite"]["height"],
            components["sprite"]["src_rect"]["x"],
            components["sprite"]["src_rect"]["y"]);
      }

      //* TransformComponent
      sol::optional<sol::table> hasTransformComponent = components["transform"];
      if (hasTransformComponent != sol::nullopt) {
        newEntity.addComponent<TransformComponent>(
            glm::vec2(components["transform"]["position"]["x"],
                      components["transform"]["position"]["y"]),
            glm::vec2(components["transform"]["scale"]["x"],
                      components["transform"]["scale"]["y"]),
            components["transform"]["rotation"]);
      }

      //* ScriptComponent
      sol::optional<sol::table> hasScriptComponent = components["script"];
      if (hasScriptComponent != sol::nullopt) {
        lua["update"] = sol::nil;  // Clear the update function

        std::string path = components["script"]["path"];

        lua.script_file(path);

        sol::optional<sol::function> hasUpdate = lua["update"];
        sol::function update = sol::nil;  // Clear the update function
        if (hasUpdate != sol::nullopt) {
          update = lua["update"];
        }
        newEntity.addComponent<ScriptComponent>(update);
      }
    }
    index++;
  }
}

void SceneLoader::loadScene(
    const std::string& scenePath, sol::state& lua, SDL_Renderer* renderer,
    std::unique_ptr<AssetManager>& assetManager,
    std::unique_ptr<ControllerManager>& controllerManager,
    std::unique_ptr<Register>& registry) {
  sol::load_result script_result = lua.load_file(scenePath);
  if (!script_result.valid()) {
    sol::error error = script_result;
    std::cerr << "[ScreenLoader] Error loading script: " << error.what()
              << std::endl;
    return;
  }
  lua.script_file(scenePath);
  sol::table scene = lua["scene"];

  sol::table sprites = scene["sprites"];
  loadSprites(renderer, sprites, assetManager);

  sol::table keyBindings = scene["keys"];
  loadKeyBindings(keyBindings, controllerManager);

  sol::table entities = scene["entities"];
  loadEntities(lua, entities, registry);
}