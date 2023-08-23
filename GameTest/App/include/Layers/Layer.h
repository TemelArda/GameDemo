#pragma once
#include <string>
#include "../Event/Event.h"

namespace Core
{
class Layer
{
public:

	Layer(const std::string& name) : mName(name) {}

	~Layer() = default;

	Layer(const Layer&) = default;

	Layer& operator=(const Layer&) = default;

	Layer(Layer&&) = default;

	Layer& operator=(Layer&&) = default;

	const std::string& GetName() const { return mName; }

	virtual void OnAttach() = 0;

	virtual void OnDetach() = 0;

	virtual void OnUpdate(float ts) = 0;

	virtual void OnRender() = 0;

	virtual void OnEvent(IEvent& e) = 0;

	virtual void Enable() = 0;

	virtual void Disable() = 0;

private:
	std::string mName;
};
}