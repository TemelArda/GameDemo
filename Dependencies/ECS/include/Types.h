#pragma once
#include <cstdint>
#include <bitset>
#include <array>

namespace Core_ECS
{
using Entity = std::uint32_t;
using ComponentID = std::uint32_t;
using SystemID = std::uint32_t;

constexpr auto MAX_ENTITIES{ 5000 };
constexpr auto MAX_COMPONENTS{ 50 };

using BitSet = std::bitset<MAX_COMPONENTS>;
} // namespace CoreECS