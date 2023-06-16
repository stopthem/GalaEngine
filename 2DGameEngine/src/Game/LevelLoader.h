#pragma once
#include <memory>
#include <sol/sol.hpp>

class Registry;
class AssetStore;
struct SDL_Renderer;
/*
 * LevelLoader
 *
 * Class used to load levels.
 */
class LevelLoader
{
public:
	LevelLoader(Registry* registry, AssetStore* assetStore, SDL_Renderer* renderer, sol::state_view luaState);
	~LevelLoader();

public:
	void LoadLevel(int level);

private:
	void LoadAssets() const;
	void CreateTileMap() const;
	void CreateEntities();

private:
	// Used to spawn entities.
	Registry* RegistryPtr;

	// Used to load texture and fonts.
	AssetStore* AssetStorePtr;

	// Used to load textures.
	SDL_Renderer* Renderer;

	// Used to get information about the level.
	sol::state_view Lua = nullptr;
};

