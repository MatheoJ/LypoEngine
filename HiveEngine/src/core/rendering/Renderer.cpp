#include "Renderer.hpp"
#include <glm/glm.hpp>

namespace hive {

    void Renderer::beginScene(OrthographicCamera& camera, glm::vec4 backgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f))
    {
        RenderCommand::setClearColor(backgroundColor);
        RenderCommand::clear();

        m_SceneData->ViewProjectionMatrix = camera.getViewProjectionMatrix();

        //TODO: in the future we will take in parameters info on camera, light and environment to render the scene
    }

    void Renderer::endScene()
    {
    }

    void Renderer::submitGeometryToDraw(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->bind();
        RenderCommand::drawVertexArray(vertexArray);
        //TODO : in the future we will sudmit the geometry to a draw queue to be rendered in the correct order
    }

    void Renderer::submitGeometryToDraw(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
    {
        shader->uploadUniformMat4("u_ViewProjection", sceneData_->viewProjectionMatrix);
        shader->bind();
        submitGeometryToDraw(vertexArray);
    }
}