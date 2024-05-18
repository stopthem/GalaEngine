#pragma once
#include <xhash>
#include <nlohmann/json.hpp>

class Uuid
{
public:
    Uuid();

    explicit Uuid(uint64_t uuid);

    Uuid(const Uuid&) = default;

    explicit operator uint64_t() const { return uuid; }

private:
    uint64_t uuid;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Uuid, uuid)
};

// Hashing of UUID
namespace std
{
    template <>
    struct hash<Uuid>
    {
        std::size_t operator()(const Uuid& uuid) const
        {
            return hash<uint64_t>()(static_cast<uint64_t>(uuid));
        }
    };
}
