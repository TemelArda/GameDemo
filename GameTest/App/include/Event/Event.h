#pragma once
#include "EventTypes.h"
#include <string>
#include <sstream>

#define EVENT_TYPE(type)   static EventType GetStaticType(){ return EventType::##type; }\
									EventType GetType() override { return GetStaticType(); }\
									const char* GetName() override { return #type; }


namespace Core
{

class IEvent
{
public:

	virtual EventType GetType() = 0;

	virtual const char* GetName() = 0;

	virtual std::string toString()
	{
		return GetName();
	}
};

class DemoEvent : public IEvent
{
public:
	DemoEvent(int variable) 
		: mVariable(variable)
	{
	}

	inline int GetVariable(){ return mVariable; }

	EVENT_TYPE(Default);

	virtual std::string toString()
	{
		std::stringstream ss;
		ss << "Demo Event Variable: " << mVariable << std::endl;
		return ss.str();
	}

private:
	int mVariable;
};

} // namespace Core