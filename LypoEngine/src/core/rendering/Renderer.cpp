#include "Renderer.hpp"

namespace Lypo {
	void Renderer::beginScene()
    {
        RenderCommand::clear();
    }

    void Renderer::endScene()
    {
    }

    void Renderer::submitGeometryToDraw(const std::shared_ptr<VertexArray>& vertexArray)
    {
        RenderCommand::drawVertexArray(vertexArray);
        //TODO : Implement a drawing queue
    }
}