#pragma once
#include <xhash>
#include <nlohmann/json.hpp>

namespace gala
{
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
}

// Hashing of UUID
template <>
struct std::hash<gala::Uuid>
{
    size_t operator()(const gala::Uuid& uuid) const noexcept
    {
        return hash<uint64_t>()(static_cast<uint64_t>(uuid));
    }
};
