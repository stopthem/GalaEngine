#pragma once

#include "../ECS/ECS.h"

namespace gala
{
    class LevelSerializer
    {
    public:
        explicit LevelSerializer(Registry* registry);

    private:
        Registry* RegistryPtr;

    public:
        void SerializeLevel(const std::string& levelFilePath) const;

        bool DeserializeLevel(const std::string& levelFilePath) const;
    };
};
