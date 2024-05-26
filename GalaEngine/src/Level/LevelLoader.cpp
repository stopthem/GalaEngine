#include "LevelLoader.h"
#include <string>
#include "../Game/Game.h"
#include "../Level/LevelSerializer.h"

namespace gala
{
    LevelLoader::LevelLoader(LevelSerializer* levelSerializer)
        : LevelSerializerPtr(levelSerializer)
    {
    }

    void LevelLoader::SaveLevel() const
    {
        LevelSerializerPtr->SerializeLevel("./assets/Levels/Level" + std::to_string(CurrentLevelIndex) + ".json");
    }


    void LevelLoader::LoadLevel(const int level)
    {
        CurrentLevelIndex = level;

        LevelSerializerPtr->DeserializeLevel("./assets/Levels/Level" + std::to_string(level) + ".json");
    }
}
