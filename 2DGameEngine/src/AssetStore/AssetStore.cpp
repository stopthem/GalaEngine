#include "AssetStore.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../Logger/Logger.h"

AssetStore::~AssetStore()
{
	ClearAssets();
}

void AssetStore::ClearAssets()
{
	for (const auto& [assetId, texture] : Textures)
	{
		SDL_DestroyTexture(texture);
	}

	Textures.clear();

	for (const auto& [assetId, font] : Fonts)
	{
		TTF_CloseFont(font);
	}

	Fonts.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if (!surface)
	{
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture)
	{
		return;
	}

	Textures.emplace(assetId, texture);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId)
{
	return Textures[assetId];
}

void AssetStore::AddFont(const std::string& assetId, const std::string& filePath, const int size)
{
	Fonts.emplace(assetId, TTF_OpenFont(filePath.c_str(), size));
}

TTF_Font* AssetStore::GetFont(const std::string& assetId) const
{
	return Fonts.at(assetId);
}
