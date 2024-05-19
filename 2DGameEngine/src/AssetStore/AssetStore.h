#pragma once
#include <map>
#include <string>
#include <SDL_ttf.h>

struct SDL_Renderer;
struct SDL_Texture;

namespace gala
{
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

    private:
        SDL_Renderer* Renderer = nullptr;

    public:
        void Initialize(::SDL_Renderer* renderer);

        void ClearAssets();

    private:
        void LoadAssetsUnderAssetsFolder();

    public:
        void AddTexture(const std::string& filePath);

        [[nodiscard]] SDL_Texture* GetTexture(const std::string& filePath);

    public:
        void AddFont(const std::string& filePath);

        [[nodiscard]] TTF_Font* GetFont(const std::string& filePath, int fontSize) const;
    };
}
