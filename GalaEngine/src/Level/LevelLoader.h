#pragma once
#include <sol/sol.hpp>

struct SDL_Renderer;

namespace gala
{
    class LevelSerializer;
    struct IComponent;
    class Registry;
    class AssetStore;

    /*
 * LevelLoader
 *
 * Class used to load levels.
 */
    class LevelLoader
    {
    public:
        explicit LevelLoader(LevelSerializer* levelSerializer);

    public:
        void SaveLevel() const;

        void LoadLevel(int level);

    private:
        // Used to serialize level
        LevelSerializer* LevelSerializerPtr = nullptr;

    private:
        int CurrentLevelIndex = -1;
    };
}
