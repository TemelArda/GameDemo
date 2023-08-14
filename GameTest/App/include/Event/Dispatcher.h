#pragma once
#include "Event.h"
#include <functional>
#include <vector>
#include <array>

namespace Core
{

#define BIND_LISTENER_FUNCTION(Instance, ListenerFunction) std::bind(&ListenerFunction, Instance, std::placeholders::_1)


class Dispatcher
{

using callback = std::function< void(IEvent&) >;

public:

	void Subscribe(callback&& cb, EventType event);

	void UnSubscribe(callback&& cb);

	void Dispatch(IEvent& mEvent);
private:

	std::array<std::vector<callback>, TOTAL_NUMBER_OF_EVENTS > mObservers;
};

}