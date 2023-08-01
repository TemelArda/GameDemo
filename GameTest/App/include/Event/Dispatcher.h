#pragma once
#include "Event.h"
#include <functional>
#include <vector>

namespace Core
{

#define BIND_LISTENER_FUNCTION(ListenerFunction) std::bind(&ListenerFunction, this, std::placeholders::_1)

class Dispatcher
{

using callback = std::function< void(IEvent&) >;

public:
	Dispatcher() = delete;

	Dispatcher(Dispatcher& other) = delete;

	Dispatcher(EventType e);

	void Subscribe(callback&& cb);

	void UnSubscribe(callback&& cb);

	void Dispatch(IEvent& mEvent);
private:

	std::vector<callback> mObservers;
	EventType type;
	
};

}