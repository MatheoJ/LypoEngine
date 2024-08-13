#pragma once
#include "lypch.h"
#include "VertexArray.hpp"
#include "RenderCommand.h"

namespace Lypo {

	class Renderer
	{
	public:
        static void beginScene();
        static void endScene();

        static void submitGeometryToDraw(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RenderAPI::API getApi() { return RenderAPI::getAPI(); }
	};


}