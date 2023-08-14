#pragma once
#include "Layer.h"
#include <memory>
#include <vector>

namespace Core
{
class LayerStack
{
typedef std::vector<std::shared_ptr<Layer>> LayerVector;

public:
	 LayerStack();
	 
	 ~LayerStack() = default;

	 LayerStack(const LayerStack&) = delete;

	LayerStack& operator=(const LayerStack&) = delete;

	LayerStack(LayerStack&&) = default;

	LayerStack& operator=(LayerStack&&) = default;

	 void PushLayer(std::shared_ptr<Layer> layer);

	 void PushOverlay(std::shared_ptr<Layer> overlay);
	 
	 void PopLayer(std::shared_ptr<Layer> layer);
	 
	 void PopOverlay(std::shared_ptr<Layer> overlay);

	 LayerVector::iterator begin() { return mLayers.begin(); }
	 
	 LayerVector::iterator end() { return mLayers.end(); }
private:
	LayerVector mLayers;

	LayerVector::iterator mLayerInsert;
};

} // namespace Core