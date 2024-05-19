#include "AssetStore.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../Logger/Logger.h"
#include "glm/gtx/matrix_interpolation.hpp"

namespace gala
{
    AssetStore::~AssetStore()
    {
        ClearAssets();
    }

    void AssetStore::LoadAssetsUnderAssetsFolder()
    {
        // Iterate through every file under ./assets
        for (const auto& entry : std::filesystem::recursive_directory_iterator("./assets"))
        {
            // if entry is a valid file
            if (!entry.is_regular_file() || entry.is_symlink())
            {
                continue;
            }

            // Store path of the entry
            const std::string entryPath = entry.path().generic_string();

            // If entry path ends with ".tff" it's a font
            if (entryPath.ends_with(".ttf"))
            {
                AddFont(entryPath);
                continue;
            }

            // If entry path ends with ".png" it's a texture
            if (entryPath.ends_with(".png"))
            {
                AddTexture(entryPath);
            }
        }
    }

    void AssetStore::Initialize(SDL_Renderer* renderer)
    {
        Renderer = renderer;

        // We want to load every asset we can before level start
        LoadAssetsUnderAssetsFolder();
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

    void AssetStore::AddTexture(const std::string& filePath)
    {
        SDL_Surface* surface = IMG_Load(filePath.c_str());

        if (!surface)
        {
            return;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);

        if (!texture)
        {
            return;
        }

        Textures.emplace(filePath, texture);
    }

    SDL_Texture* AssetStore::GetTexture(const std::string& filePath)
    {
        assert(Textures.contains(filePath));

        return Textures[filePath];
    }

    void AssetStore::AddFont(const std::string& filePath)
    {
        Fonts.emplace(filePath, TTF_OpenFont(filePath.c_str(), 0));
    }

    TTF_Font* AssetStore::GetFont(const std::string& filePath, const int fontSize) const
    {
        assert(Fonts.contains(filePath));

        // Find the correct TTF_Font
        TTF_Font* font = Fonts.at(filePath);
        // Resize font to the wanted size
        TTF_SetFontSize(font, fontSize);
        return font;
    }
}
