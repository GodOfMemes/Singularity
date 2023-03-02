#pragma once

#include <random>

namespace RNG
{
    std::random_device randomDevice;
    std::mt19937_64 eng(randomDevice());
    std::uniform_int_distribution<unsigned long long>  distribution;

    inline uint64_t GetRandomUInt64()
    {
        return distribution(eng);
    }
}