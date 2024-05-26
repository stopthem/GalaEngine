#pragma once
#include <string>
#include <nlohmann/json.hpp>


namespace gala
{
    /*
     * NameComponent
     *
     * Component that holds a single name for the entity
     */
    struct NameComponent
    {
    public:
        NameComponent() = default;
        
        explicit NameComponent(const std::string& inName);

    public:
        std::string Name;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NameComponent, Name)
    };
}
