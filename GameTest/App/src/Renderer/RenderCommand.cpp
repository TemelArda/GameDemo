#include "stdafx.h"
#include "../../include/Renderer/RenderCommand.h"
#include "../../include/Renderer/OpenGLRendererAPI.h"

namespace Core_Renderer
{
	IRendererAPI* RenderCommand::mAPI = new OpenGLRendererAPI;
}