#include "UUID.h"
#include <random>

static std::random_device RandomDevice;
static std::mt19937_64 RandomEngine(RandomDevice());
static std::uniform_int_distribution<uint64_t> UniformIntDistribution;

Uuid::Uuid() : uuid(UniformIntDistribution(RandomEngine))
{
}

Uuid::Uuid(const uint64_t uuid) : uuid(uuid)
{
}
