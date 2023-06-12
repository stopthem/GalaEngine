#pragma once
#include <map>
#include <string>

struct SDL_Renderer;
struct SDL_Texture;
/*
 * AssetStore
 *
 * Handles fonts, audios and textures loading and getting with their ids.
 */
class AssetStore
{
public:
	AssetStore();
	~AssetStore();

private:
	std::map<std::string, SDL_Texture*> Textures;
	// TODO: create a map for fonts
	// TODO: create a map for audios

public:
	void ClearAssets();
	void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);

	[[nodiscard]] SDL_Texture* GetTexture(const std::string& assetId);
};

