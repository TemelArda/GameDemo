#include "stdafx.h"
#include "../../include/Event/Dispatcher.h"
#include "Logger.h"

namespace Core
{
Dispatcher::Dispatcher(EventType event)
{
	type = event;
}

void Dispatcher::Subscribe(callback&& cb)
{
	mObservers.push_back(cb);
}

void Dispatcher::UnSubscribe(callback&& cb)
{
	//TODO Implement
	//mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), cb), mObservers.end());
}

void Dispatcher::Dispatch(IEvent& mEvent)
{
	if(mEvent.GetType() != type)
		return;
	for (auto& cb : mObservers)
	{
		cb(mEvent);
	}
}
} // namespace Core