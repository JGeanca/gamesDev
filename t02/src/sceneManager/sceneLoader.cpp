#include "sceneLoader.hpp"

#include <glm/glm.hpp>
#include <iostream>

#include "../components/animationComponent.hpp"
#include "../components/boxColliderComponent.hpp"
#include "../components/cameraFollowComponent.hpp"
#include "../components/circleColliderComponent.hpp"
#include "../components/clickableComponent.hpp"
#include "../components/healthComponent.hpp"
#include "../components/rigidBodyComponent.hpp"
#include "../components/scriptComponent.hpp"
#include "../components/spriteComponent.hpp"
#include "../components/tagComponent.hpp"
#include "../components/textComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../game/game.hpp"
#include "../utils/debug.hpp"

SceneLoader::SceneLoader() { DEBUG_MSG("[SceneLoader] SceneLoader created"); }

SceneLoader::~SceneLoader() {
  DEBUG_MSG("[SceneLoader] SceneLoader destroyed");
}

void SceneLoader::loadMap(const sol::table& map,
                          std::unique_ptr<Register>& registry) {
  sol::optional<int> hasWidth = map["width"];
  if (hasWidth != sol::nullopt) {
    Game::getInstance().mapWidth = map["width"];
  }

  sol::optional<int> hasHeight = map["height"];
  if (hasHeight != sol::nullopt) {
    Game::getInstance().mapHeight = map["height"];
  }

  sol::optional<std::string> hasPath = map["map_path"];
  if (hasPath != sol::nullopt) {
    std::string mapPath = map["map_path"];

    tinyxml2::XMLDocument xmlmap;
    xmlmap.LoadFile(mapPath.c_str());

    tinyxml2::XMLElement* xmlRoot = xmlmap.RootElement();

    int tWidth, tHeight, mWidth, mHeight;
    xmlRoot->QueryIntAttribute("tilewidth", &tWidth);
    xmlRoot->QueryIntAttribute("tileheight", &tHeight);
    xmlRoot->QueryIntAttribute("width", &mWidth);
    xmlRoot->QueryIntAttribute("height", &mHeight);

    Game::getInstance().mapWidth = mWidth * tWidth;
    Game::getInstance().mapHeight = mHeight * tHeight;

    std::string tilePath = map["tile_path"];  // tile set path
    std::string tileName = map["tile_name"];  // tile set name

    tinyxml2::XMLDocument xmltileset;
    xmltileset.LoadFile(tilePath.c_str());

    int columns;
    tinyxml2::XMLElement* xmlTilesetRoot = xmltileset.RootElement();
    xmlTilesetRoot->QueryIntAttribute("columns", &columns);

    tinyxml2::XMLElement* xmlLayer = xmlRoot->FirstChildElement("layer");

    while (xmlLayer) {
      loadLayer(registry, xmlLayer, tWidth, tHeight, mWidth, tileName, columns);
      xmlLayer = xmlLayer->NextSiblingElement("layer");
    }
  }
}

void SceneLoader::loadLayer(std::unique_ptr<Register>& registry,
                            tinyxml2::XMLElement* layer, int tWidth,
                            int tHeight, int mWidth, const std::string& tileSet,
                            int columns) {
  tinyxml2::XMLElement* xmlData = layer->FirstChildElement("data");
  const char* data = xmlData->GetText();

  std::stringstream tmpNum;
  int pos = 0;
  int tileNum = 0;

  while (true) {
    if (data[pos] == '\0') {
      break;
    }
    if (isdigit(data[pos])) {
      tmpNum << data[pos];
    } else if (!isdigit(data[pos]) && tmpNum.str().length() != 0) {
      int tiledId = std::stoi(tmpNum.str());
      if (tiledId > 0) {
        Entity tile = registry->createEntity();
        tile.addComponent<TransformComponent>(
            glm::vec2((tileNum % mWidth) * tWidth,
                      (tileNum / mWidth) * tHeight),
            glm::vec2(1, 1), 0);

        tile.addComponent<SpriteComponent>(tileSet, tWidth, tHeight,
                                           ((tiledId - 1) % columns) * tWidth,
                                           ((tiledId - 1) / columns) * tHeight);
      }
      tileNum++;
      tmpNum.str("");
    }
    pos++;
  }
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
    assetManager->addTexture(renderer, id, path);

    index++;
  }
}

void SceneLoader::loadFonts(const sol::table& fonts,
                            std::unique_ptr<AssetManager>& assetManager) {
  int index = 0;

  while (true) {
    sol::optional<sol::table> hasFont = fonts[index];
    if (hasFont == sol::nullopt) {
      break;
    }
    sol::table font = fonts[index];

    std::string id = font["fontId"];
    std::string path = font["filePath"];
    int size = font["fontSize"];
    assetManager->addFont(id, path, size);

    index++;
  }
}

void SceneLoader::loadSounds(const sol::table& sounds,
                             std::unique_ptr<AudioManager>& audioManager) {
  sol::table soundEffects = sounds["sound_effects"];
  sol::table music = sounds["music"];

  for (const auto& sound : soundEffects) {
    std::string name = sound.first.as<std::string>();
    std::string path = sound.second.as<std::string>();
    audioManager->loadSoundEffect(name, path);
  }

  for (const auto& song : music) {
    std::string name = song.first.as<std::string>();
    std::string path = song.second.as<std::string>();
    audioManager->loadMusic(name, path);
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

void SceneLoader::loadMouseBindings(
    const sol::table& mouseBindings,
    std::unique_ptr<ControllerManager>& controllerManager) {
  int index = 0;
  while (true) {
    sol::optional<sol::table> hasMouseButtons = mouseBindings[index];
    if (hasMouseButtons == sol::nullopt) {
      break;
    }
    sol::table mouseButton = mouseBindings[index];
    std::string name = mouseButton["name"];
    int mouseButtonCode = mouseButton["key"];

    controllerManager->addMouseButton(name, mouseButtonCode);

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

      addTagComponent(newEntity, components);
      addAnimationComponent(newEntity, components);
      addCircleColliderComponent(newEntity, components);
      addBoxColliderComponent(newEntity, components);
      addRigidBodyComponent(newEntity, components);
      addSpriteComponent(newEntity, components);
      addTextComponent(newEntity, components);
      addClickableComponent(newEntity, components);
      addTransformComponent(newEntity, components);
      addScriptComponent(newEntity, components, lua);
      addHealthComponent(newEntity, components);
      addCameraFollowComponent(newEntity, components);
    }

    index++;
  }
}

void SceneLoader::loadScene(
    const std::string& scenePath, sol::state& lua, SDL_Renderer* renderer,
    std::unique_ptr<AssetManager>& assetManager,
    std::unique_ptr<ControllerManager>& controllerManager,
    std::unique_ptr<AudioManager>& audioManager,
    std::unique_ptr<Register>& registry) {
  sol::load_result script_result = lua.load_file(scenePath);
  if (!script_result.valid()) {
    sol::error error = script_result;
    std::cerr << "[SceneLoader] Error loading script: " << error.what()
              << std::endl;
    return;
  }
  lua.script_file(scenePath);
  sol::table scene = lua["scene"];

  sol::table sprites = scene["sprites"];
  loadSprites(renderer, sprites, assetManager);

  sol::table audio = scene["audio"];
  loadSounds(audio, audioManager);

  sol::table fonts = scene["fonts"];
  loadFonts(fonts, assetManager);

  sol::table keyBindings = scene["keys"];
  loadKeyBindings(keyBindings, controllerManager);

  sol::table mouseBindings = scene["mouse_buttons"];
  loadMouseBindings(mouseBindings, controllerManager);

  sol::protected_function init_level = lua["init_level"];
  if (init_level.valid()) {
    auto result = init_level();
    if (!result.valid()) {
      sol::error err = result;
      std::cerr << "Error executing init_level: " << err.what() << std::endl;
    }
  }

  sol::table maps = scene["maps"];
  loadMap(maps, registry);

  sol::table entities = scene["entities"];
  loadEntities(lua, entities, registry);
}

void SceneLoader::addTagComponent(Entity& entity,
                                  const sol::table& components) {
  sol::optional<sol::table> hasTagComponent = components["tag"];
  if (hasTagComponent != sol::nullopt) {
    std::string tag = components["tag"]["tag"];
    entity.addComponent<TagComponent>(tag);
  }
}

void SceneLoader::addAnimationComponent(Entity& entity,
                                        const sol::table& components) {
  sol::optional<sol::table> hasAnimateComponent = components["animation"];
  if (hasAnimateComponent != sol::nullopt) {
    entity.addComponent<AnimationComponent>(
        components["animation"]["num_frames"],
        components["animation"]["speed_rate"],
        components["animation"]["is_loop"]);
  }
}

void SceneLoader::addCircleColliderComponent(Entity& entity,
                                             const sol::table& components) {
  sol::optional<sol::table> hasColliderComponent =
      components["circle_collider"];
  if (hasColliderComponent != sol::nullopt) {
    entity.addComponent<CircleColliderComponent>(
        components["circle_collider"]["radius"],
        components["circle_collider"]["width"],
        components["circle_collider"]["height"]);
  }
}

void SceneLoader::addBoxColliderComponent(Entity& entity,
                                          const sol::table& components) {
  sol::optional<sol::table> hasBoxColliderComponent =
      components["box_collider"];
  if (hasBoxColliderComponent != sol::nullopt) {
    entity.addComponent<BoxColliderComponent>(
        components["box_collider"]["width"],
        components["box_collider"]["height"],
        glm::vec2(components["box_collider"]["offset"]["x"],
                  components["box_collider"]["offset"]["y"]));
  }
}

void SceneLoader::addRigidBodyComponent(Entity& entity,
                                        const sol::table& components) {
  sol::optional<sol::table> hasRigidBodyComponent = components["rg_body"];

  if (hasRigidBodyComponent != sol::nullopt) {
    entity.addComponent<RigidBodyComponent>(
        glm::vec2(components["rg_body"]["velocity"]["x"],
                  components["rg_body"]["velocity"]["y"]));
  }
}

void SceneLoader::addSpriteComponent(Entity& entity,
                                     const sol::table& components) {
  sol::optional<sol::table> hasSpriteComponent = components["sprite"];
  if (hasSpriteComponent != sol::nullopt) {
    entity.addComponent<SpriteComponent>(
        components["sprite"]["assetId"], components["sprite"]["width"],
        components["sprite"]["height"], components["sprite"]["src_rect"]["x"],
        components["sprite"]["src_rect"]["y"]);
  }
}

void SceneLoader::addTextComponent(Entity& entity,
                                   const sol::table& components) {
  sol::optional<sol::table> hasTextComponent = components["text"];
  if (hasTextComponent != sol::nullopt) {
    entity.addComponent<TextComponent>(
        components["text"]["text"], components["text"]["fontId"],
        components["text"]["r"], components["text"]["g"],
        components["text"]["b"], components["text"]["a"]

    );
  }
}

void SceneLoader::addClickableComponent(Entity& entity,
                                        const sol::table& components) {
  sol::optional<sol::table> hasClickableComponent = components["clickable"];
  if (hasClickableComponent != sol::nullopt) {
    entity.addComponent<ClickableComponent>();
  }
}

void SceneLoader::addTransformComponent(Entity& entity,
                                        const sol::table& components) {
  sol::optional<sol::table> hasTransformComponent = components["transform"];
  if (hasTransformComponent != sol::nullopt) {
    entity.addComponent<TransformComponent>(
        glm::vec2(components["transform"]["position"]["x"],
                  components["transform"]["position"]["y"]),
        glm::vec2(components["transform"]["scale"]["x"],
                  components["transform"]["scale"]["y"]),
        components["transform"]["rotation"]);
  }
}

void SceneLoader::addScriptComponent(Entity& entity,
                                     const sol::table& components,
                                     sol::state& lua) {
  sol::optional<sol::table> hasScriptComponent = components["script"];
  if (hasScriptComponent != sol::nullopt) {
    entity.addComponent<ScriptComponent>();
    auto& scriptComponent = entity.getComponent<ScriptComponent>();

    sol::table scripts = components["script"];
    for (auto& script : scripts) {
      std::string path = script.second.as<std::string>();
      lua.script_file(path);

      if (lua["update"].valid()) {
        scriptComponent.updateFunctions.push_back(lua["update"]);
      }
      if (lua["on_click"].valid()) {
        scriptComponent.onClickFunctions.push_back(lua["on_click"]);
      }
      if (lua["init"].valid()) {
        scriptComponent.initFunctions.push_back(lua["init"]);
      }
      if (lua["on_collision"].valid()) {
        scriptComponent.onCollisionFunctions.push_back(lua["on_collision"]);
      }

      // Clear the global functions after adding them to the component
      lua["update"] = sol::nil;
      lua["on_click"] = sol::nil;
      lua["init"] = sol::nil;
      lua["on_collision"] = sol::nil;
    }
  }
}

void SceneLoader::addHealthComponent(Entity& entity,
                                     const sol::table& components) {
  sol::optional<sol::table> hasHealthComponent = components["health"];
  if (hasHealthComponent != sol::nullopt) {
    entity.addComponent<HealthComponent>(
        components["health"]["max_health"],
        components["health"]["regeneration_rate"]);
  }
}

void SceneLoader::addCameraFollowComponent(Entity& entity,
                                           const sol::table& components) {
  sol::optional<sol::table> hasCameraFollowComponent =
      components["camera_follow"];
  if (hasCameraFollowComponent != sol::nullopt) {
    entity.addComponent<CameraFollowComponent>();
  }
}