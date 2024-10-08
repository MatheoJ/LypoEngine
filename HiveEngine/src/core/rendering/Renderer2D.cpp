//
// Created by mathe on 02/10/2024.
//

#include "Renderer2D.h"
#include "platform/opengl/opengl_shader.h"
#include "RenderCommand.h"



namespace hive {

    static Renderer2DStorage* s_Data =nullptr;

    void Renderer2D::init()
    {
        float quadVertices[ 3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        uint32_t quadIndices[6] = { 0, 1, 2, 2, 3, 0 };

        s_Data = new hive::Renderer2DStorage();

        s_Data->QuadVertexArray.reset(hive::VertexArray::create());
        SRef<hive::VertexBuffer> quadVB;
        quadVB.reset(hive::VertexBuffer::create(quadVertices, sizeof(quadVertices)));
        quadVB->setLayout({
            { hive::ShaderDataType::Float3, "a_Position" }
        });
        s_Data->QuadVertexArray->addVertexBuffer(quadVB);

        SRef<hive::IndexBuffer> quadIB;
        quadIB.reset(hive::IndexBuffer::create(quadIndices, sizeof(quadIndices)));
        s_Data->QuadVertexArray->setIndexBuffer(quadIB);

        std::string fragmentPathflatColor = "../HiveEngine/assets/shaders/flatColor.frag.glsl";
        std::string vertexPathflatColor = "../HiveEngine/assets/shaders/flatColor.vert.glsl";

        s_Data->FlatColorShader = std::make_shared<hive::OpenglShader>(vertexPathflatColor, fragmentPathflatColor);
    }
    void Renderer2D::shutdown()
    {
        delete s_Data;
    }
    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        std::dynamic_pointer_cast<hive::OpenglShader>(s_Data->FlatColorShader)->bind();
        std::dynamic_pointer_cast<hive::OpenglShader>(s_Data->FlatColorShader)->uploadUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());
        std::dynamic_pointer_cast<hive::OpenglShader>(s_Data->FlatColorShader)->uploadUniformMat4("u_Transform", glm::mat4(1.0f));
    }
    void Renderer2D::endScene()
    {
    }
    void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        drawQuad({ position.x, position.y, 0.0f }, size, color);
    }
    void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        std::dynamic_pointer_cast<hive::OpenglShader>(s_Data->FlatColorShader)->bind();
        std::dynamic_pointer_cast<hive::OpenglShader>(s_Data->FlatColorShader)->uploadUniformFloat4("u_Color", color);
        s_Data->QuadVertexArray->bind();
        hive::RenderCommand::drawVertexArray(s_Data->QuadVertexArray);
    }
}