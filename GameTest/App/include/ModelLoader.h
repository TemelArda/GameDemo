#pragma once
#include "./Renderer/VertexArray.h"
#include <string>
#include <optional>

namespace Core
{

std::optional<std::shared_ptr<Core_Renderer::VertexArray>> LoadObj(const std::string& path);

}