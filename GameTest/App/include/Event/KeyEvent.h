#pragma once
#include "Event.h"
#include <sstream>

namespace Core
{
class KeyPressedEvent : public IEvent
{
public:
	KeyPressedEvent() = default;

	EVENT_TYPE(KeyPressed);

	virtual std::string toString()
	{
		std::stringstream ss;
		ss << "Demo Event Variable: " << mVariable << std::endl;
		return ss.str();
	}

private:
	int mVariable;
};

}
