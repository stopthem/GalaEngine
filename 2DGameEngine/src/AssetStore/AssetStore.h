#pragma once
#include <map>
#include <string>
#include <SDL_ttf.h>

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
	AssetStore() = default;
	~AssetStore();

private:
	std::map<std::string, SDL_Texture*> Textures;
	std::map<std::string, TTF_Font*> Fonts;
	// TODO: create a map for audios

public:
	void ClearAssets();

public:
	void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);

	[[nodiscard]] SDL_Texture* GetTexture(const std::string& assetId);

public:

	void AddFont(const std::string& assetId, const std::string& filePath, int size);

	[[nodiscard]] TTF_Font* GetFont(const std::string& assetId) const;
};

