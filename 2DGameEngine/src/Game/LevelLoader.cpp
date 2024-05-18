#include "LevelLoader.h"
#include <fstream>
#include <string>
#include <vector>
#include "Game.h"
#include "glm/vec2.hpp"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/LifetimeComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/HealthBarComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/ShootingComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Logger/Logger.h"
#include "../Scene/LevelSerializer.h"
#include "../Utility/StringUtilities.h"

LevelLoader::LevelLoader(Registry* registry, AssetStore* assetStore, SDL_Renderer* renderer, LevelSerializer* levelSerializer, sol::state_view luaState)
    : RegistryPtr(registry), AssetStorePtr(assetStore), Renderer(renderer), LuaStateView(std::move(luaState)), LevelSerializerPtr(levelSerializer)
{
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::SaveLevel()
{
    LevelSerializerPtr->SerializeLevel("./assets/Levels/Level" + std::to_string(CurrentLevelIndex) + ".json");
}


void LevelLoader::LoadLevel(const int level)
{
    CurrentLevelIndex = level;
    
    LevelSerializerPtr->DeserializeLevel("./assets/Levels/Level" + std::to_string(level) + ".json");
    // const std::string levelFile = "./assets/scripts/Level" + std::to_string(level) + ".lua";
    //
    // // Check if our script had an error when loading and log it.
    // if (const sol::load_result script = LuaStateView.load_file(levelFile); !script.valid())
    // {
    //     const sol::error err = script;
    //
    //     const std::string errMessage = err.what();
    //
    //     Logger::Err("Error loading the lua script in" + levelFile + " error : " + errMessage);
    //
    //     return;
    // }
    //
    // LuaStateView.script_file(levelFile);
    //
    // LoadAssets();
    //
    // CreateTileMap();
    //
    // CreateEntities();
}

void LevelLoader::LoadAssets() const
{
    // const sol::table assetsTable = LuaStateView["Level"]["assets"];
    //
    // // Go until assetsTable.size() + 1 because sol probably ignores last element because Lua starts indexes with 1.
    // for (int i = 0; i < static_cast<int>(assetsTable.size()) + 1; ++i)
    // {
    //     // This is the actual table that holds the values.
    //     const sol::table assetTable = assetsTable[i];
    //
    //     const std::string assetType = assetTable["type"];
    //     const std::string assetId = assetTable["id"];
    //     const std::string assetPath = assetTable["file"];
    //
    //     if (assetType == "font")
    //     {
    //         AssetStorePtr->AddFont(assetId, assetPath, assetTable["font_size"]);
    //     }
    //     else if (assetType == "texture")
    //     {
    //         AssetStorePtr->AddTexture(Renderer, assetId, assetPath);
    //     }
    // }
}

void LevelLoader::CreateTileMap() const
{
    //     const sol::table tilemapTable = LuaStateView["Level"]["tilemap"];
    //
    //     // First, lets read the .map file and get tile numbers for the tilemaps.
    //     std::vector<int> tileNumbers;
    //
    //     const std::string mapFile = tilemapTable["map_file"];
    //     // This automatically opens the file for us to read.
    //     std::ifstream readFile(mapFile);
    //
    //     std::string lineString;
    //     while (std::getline(readFile, lineString))
    //     {
    //         // Split line elements by ",".
    //         // This function is very useful and it gives us raw numbers without spaces.
    //         std::vector<std::string> splitLineNumberStrings = StringUtilities::Split(lineString, ",");
    //
    //         // When we split a string, it gives us a vector of strings with numbers. Iterate through them to add to list.
    //         for (const std::string& lineNumberString : splitLineNumberStrings)
    //         {
    //             // Convert string to int and add to vector.
    //             tileNumbers.push_back(std::stoi(lineNumberString));
    //         }
    //     }
    //
    //     const double tileScale = tilemapTable["scale"];
    //     const int tileSize = tilemapTable["tile_size"];
    //     const int numRows = tilemapTable["num_rows"];
    //     const int numColumns = tilemapTable["num_cols"];
    //     const std::string textureAssetId = tilemapTable["texture_asset_id"];
    //
    //     // Then iterate through .map file columns and rows
    //     for (int y = 0; y < numRows; ++y)
    //     {
    //         for (int x = 0; x < numColumns; ++x)
    //         {
    //             // Find 1d pos of a 2d value in the vector.
    //             const int tileNumber = tileNumbers[(y * numColumns) + x];
    //
    //             // Find x tiling of the image which is 10x3.
    //             const int textureTilingX = (tileNumber % 10) * tileSize;
    //             // Find y tiling of the image which is 10x3.
    //             const int textureTilingY = (tileNumber / 10) * tileSize;
    //
    //             Entity entity = RegistryPtr->CreateEntity();
    //
    //             // We have to leave space between for tileSize(32) * tileScale because image is 32x32.
    //             const glm::vec2 entityLocation(x * (tileSize * tileScale), y * (tileSize * tileScale));
    //
    //             entity.AddComponent<TransformComponent>(entityLocation, glm::vec2(static_cast<float>(tileScale)), 0.0);
    //
    //             entity.AddComponent<SpriteComponent>(textureAssetId, tileSize, tileSize, 0, false, true, glm::vec2(textureTilingX, textureTilingY));
    //
    //             entity.AddToGroup(GROUP_TILEMAP);
    //         }
    //     }
    //
    //     Game::MapWidth = (numColumns * tileSize) * tileScale;
    //     Game::MapHeight = (numRows * tileSize) * tileScale;
    // // }
    //
    // void LevelLoader::CreateEntities()
    // {
    //     const sol::table entitiesTable = LuaStateView["Level"]["entities"];
    //
    //     // Go until entitiesTable.size() + 1 because sol probably ignores last element because Lua starts indexes with 1.
    //     for (int i = 0; i < static_cast<int>(entitiesTable.size()) + 1; ++i)
    //     {
    //         // Everything about entity is in this table.
    //         const sol::table entityTable = entitiesTable[i];
    //
    //         Entity entity = RegistryPtr->CreateEntity();
    //
    //         // Check tag and add if exists.
    //         if (entityTable["tag"].valid())
    //         {
    //             entity.AddTag(entityTable["tag"]);
    //         }
    //
    //         // Check group and add if exists.
    //         if (entityTable["group"].valid())
    //         {
    //             entity.AddToGroup(entityTable["group"]);
    //         }
    //
    //         // All the components is in this table.
    //         const sol::table componentsTable = entityTable["components"];
    //
    //         for (const auto& [key, value] : componentsTable)
    //         {
    //             // Key is component name.
    //             const std::string componentName = key.as<std::string>();
    //
    //             // Value is component's table of values.
    //             const sol::table componentValuesTable = value;
    //
    //             if (componentName == "transform")
    //             {
    //                 const sol::table locationTable = componentValuesTable["location"];
    //                 glm::vec2 location = {locationTable["x"], locationTable["y"]};
    //
    //                 const sol::table scaleTable = componentValuesTable["scale"];
    //                 glm::vec2 scale = {scaleTable["x"].get_or(1.0), scaleTable["y"].get_or(1.0)};
    //
    //                 const double angle = componentValuesTable["rotation"].get_or(0.0);
    //
    //                 entity.AddComponent<TransformComponent>(location, scale, angle);
    //             }
    //
    //             if (componentName == "rigidbody")
    //             {
    //                 const sol::table velocityTable = componentValuesTable["velocity"];
    //                 glm::vec2 velocity = {velocityTable["x"], velocityTable["y"]};
    //
    //                 entity.AddComponent<RigidbodyComponent>(velocity);
    //             }
    //
    //             if (componentName == "sprite")
    //             {
    //                 const std::string assetId = componentValuesTable["texture_asset_id"];
    //
    //                 const int width = componentValuesTable["width"];
    //                 const int height = componentValuesTable["height"];
    //
    //                 const int zIndex = componentValuesTable["z_index"];
    //
    //                 const bool isFixed = componentValuesTable["fixed"];
    //
    //                 const bool always0Angle = componentValuesTable["always_zero_angle"].get_or(false);
    //
    //                 glm::vec2 srcRect = glm::vec2(0);
    //
    //                 if (componentValuesTable["src_rect"].valid())
    //                 {
    //                     const sol::table srcRectTable = componentValuesTable["src_rect"];
    //                     srcRect = {srcRectTable["x"], srcRectTable["y"]};
    //                 }
    //
    //                 entity.AddComponent<SpriteComponent>(assetId, width, height, zIndex, isFixed, always0Angle, srcRect);
    //             }
    //
    //             if (componentName == "animation")
    //             {
    //                 const int numFrames = componentValuesTable["num_frames"];
    //                 const int speedRate = componentValuesTable["speed_rate"];
    //                 const bool looping = componentValuesTable["loop"].get_or(true);
    //
    //                 entity.AddComponent<AnimationComponent>(numFrames, speedRate, looping);
    //             }
    //
    //             if (componentName == "box_collider")
    //             {
    //                 const int width = componentValuesTable["width"];
    //                 const int height = componentValuesTable["height"];
    //
    //                 glm::vec2 offset = glm::vec2(0);
    //                 if (componentValuesTable["offset"].valid())
    //                 {
    //                     const sol::table offsetTable = componentValuesTable["offset"];
    //                     offset = {offsetTable["x"], offsetTable["y"]};
    //                 }
    //
    //                 entity.AddComponent<BoxColliderComponent>(width, height, offset);
    //             }
    //
    //             if (componentName == "health")
    //             {
    //                 const double startingHealth = componentValuesTable["starting_health"];
    //
    //                 entity.AddComponent<HealthComponent>(startingHealth);
    //             }
    //
    //             if (componentName == "healthBar")
    //             {
    //                 entity.AddComponent<HealthBarComponent>();
    //             }
    //
    //             if (componentName == "shooting")
    //             {
    //                 const double bulletSpeed = componentValuesTable["bullet_speed"];
    //
    //                 entity.AddComponent<ShootingComponent>(ProjectileParams(glm::vec2(0), true), bulletSpeed);
    //             }
    //
    //             if (componentName == "cameraFollow")
    //             {
    //                 entity.AddComponent<CameraFollowComponent>();
    //             }
    //
    //             if (componentName == "keyboard_controller")
    //             {
    //                 const double speed = componentValuesTable["speed"];
    //
    //                 entity.AddComponent<KeyboardControlledComponent>(speed);
    //             }
    //
    //             if (componentName == "projectile_emitter")
    //             {
    //                 const sol::table projectileVectorTable = componentValuesTable["projectile_velocity"];
    //                 const glm::vec2 projectileVector = {projectileVectorTable["x"], projectileVectorTable["y"]};
    //
    //                 int projectileLifeTime = componentValuesTable["projectile_duration"];
    //                 projectileLifeTime *= 1000;
    //
    //                 int projectileEmitInterval = componentValuesTable["repeat_frequency"];
    //                 projectileEmitInterval *= 1000;
    //
    //                 const double damageAmount = componentValuesTable["hit_percentage_damage"];
    //
    //                 const bool isFriendly = componentValuesTable["friendly"];
    //
    //                 entity.AddComponent<ProjectileEmitterComponent>(
    //                     ProjectileParams(projectileVector, isFriendly, damageAmount, projectileLifeTime), projectileEmitInterval);
    //             }
    //
    //             if (componentName == "lifetime")
    //             {
    //                 int lifetimeSeconds = componentValuesTable["lifetimeSeconds"];
    //                 lifetimeSeconds *= 1000;
    //
    //                 entity.AddComponent<LifetimeComponent>(lifetimeSeconds);
    //             }
    //
    //             if (componentName == "text")
    //             {
    //                 const sol::table locationTable = componentValuesTable["location"];
    //                 const glm::vec2 location = {locationTable["x"], locationTable["y"]};
    //
    //                 const std::string text = componentValuesTable["text"];
    //
    //                 const std::string fontAssetId = componentValuesTable["font-asset-id"];
    //
    //                 const SDLColorWrapper color = componentValuesTable["color"];
    //
    //                 const bool isFixed = componentValuesTable["fixed"].get_or(true);
    //
    //                 entity.AddComponent<TextComponent>(TextComponentParams(location, text, fontAssetId, color, isFixed));
    //             }
    //
    //             if (componentName == "on_update_script")
    //             {
    //                 const sol::function function = componentValuesTable[0];
    //                 entity.AddComponent<ScriptComponent>(function);
    //             }
    //         }
    //     }
}
