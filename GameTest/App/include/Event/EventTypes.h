#pragma once

namespace Core
{
constexpr const auto TOTAL_NUMBER_OF_EVENTS{3};

enum EventType
{
	Default = 0, KeyPressed, KeyReleased
};

} // namespace Core