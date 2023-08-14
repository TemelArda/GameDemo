#include "stdafx.h"
#include "../../include/Event/Dispatcher.h"
#include "Logger.h"

namespace Core
{

void Dispatcher::Subscribe(callback&& cb, EventType event)
{
	int eventIndex = (int) event;
	mObservers[eventIndex].push_back(cb);
}

void Dispatcher::UnSubscribe(callback&& cb)
{
	//TODO Implement
	//mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), cb), mObservers.end());
}

void Dispatcher::Dispatch(IEvent& event)
{	
	int eventIndex = (int)event.GetType();
	
	if(mObservers[eventIndex].empty())
		return;

	for (auto&& cb : mObservers[eventIndex])
	{
		cb(event);
	}
}
} // namespace Core