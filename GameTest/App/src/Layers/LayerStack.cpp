#include "stdafx.h"
#include "../../include/Layers/LayerStack.h"


namespace Core
{
LayerStack::LayerStack()
{
	mLayerInsert = mLayers.begin();
}

void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
{
	mLayerInsert = mLayers.emplace(mLayerInsert, layer);
}

void LayerStack::PushOverlay(std::shared_ptr<Layer> overlay)
{
	mLayers.emplace_back(overlay);
}

void LayerStack::PopLayer(std::shared_ptr<Layer> layer)
{
	auto it = std::find(mLayers.begin(), mLayers.end(), layer);
	
	if (it != mLayers.end())
	{
		mLayers.erase(it);
		mLayerInsert--;
	}
}

void LayerStack::PopOverlay(std::shared_ptr<Layer> overlay)
{
	auto it = std::find(mLayers.begin(), mLayers.end(), overlay);

	if (it != mLayers.end())
	{
		mLayers.erase(it);
	}
}
}
