#pragma once
#include <sol/sol.hpp>

class LevelSerializer;
struct IComponent;
class Registry;
class AssetStore;
struct SDL_Renderer;

struct EntityJsonSave
{
public:
    int EntityId;

    std::vector<IComponent> Components;
};

/*
 * LevelLoader
 *
 * Class used to load levels.
 */
class LevelLoader
{
public:
    LevelLoader(Registry* registry, AssetStore* assetStore, SDL_Renderer* renderer, LevelSerializer* levelSerializer, sol::state_view luaState);
    ~LevelLoader();

public:
    void SaveLevel();
    
    void LoadLevel(int level);

private:
    void LoadAssets() const;
    void CreateTileMap() const;

private:
    // Used to spawn entities.
    Registry* RegistryPtr;

    // Used to load texture and fonts.
    AssetStore* AssetStorePtr;

    // Used to load textures.
    SDL_Renderer* Renderer = nullptr;

    // Used to get information about the level.
    sol::state_view LuaStateView = nullptr;

    // Used to serialize level
    LevelSerializer* LevelSerializerPtr = nullptr;

private:
    int CurrentLevelIndex = -1;
};
