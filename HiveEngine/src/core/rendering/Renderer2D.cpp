//
// Created by mathe on 02/10/2024.
//

#include "Renderer2D.h"
#include "platform/opengl/opengl_shader.h"
#include "RenderCommand.h"
#include "platform/opengl/GLCheck.h"



namespace hive {

    static Renderer2DStorage* s_Data =nullptr;

    void Renderer2D::init()
    {
        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        s_Data = new Renderer2DStorage();
        s_Data->QuadVertexArray = SRef<VertexArray>(VertexArray::create());
        SRef<VertexBuffer> squareVB;
        squareVB = SRef<VertexBuffer>(VertexBuffer::create(squareVertices, sizeof(squareVertices)));
        squareVB->setLayout({
            { ShaderDataType::Float3, "a_Position" }
        });
        s_Data->QuadVertexArray->addVertexBuffer(squareVB);

        SRef<IndexBuffer> squareIB;
        squareIB = SRef<IndexBuffer>(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        s_Data->QuadVertexArray->setIndexBuffer(squareIB);

        std::string fragmentPath = "../HiveEngine/assets/shaders/flatColor.frag.glsl";
        std::string vertexPath = "../HiveEngine/assets/shaders/flatColor.vert.glsl";

        s_Data->FlatColorShader = std::make_shared<hive::OpenglShader>(vertexPath, fragmentPath);
        glCheckError();
    }
    void Renderer2D::shutdown()
    {
        delete s_Data;
    }
    void Renderer2D::beginScene(const OrthographicCamera& camera)
    {
        std::dynamic_pointer_cast<OpenglShader>(s_Data->FlatColorShader)->bind();
        std::dynamic_pointer_cast<OpenglShader>(s_Data->FlatColorShader)->uploadUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenglShader>(s_Data->FlatColorShader)->uploadUniformMat4("u_Transform", glm::mat4(1.0f));
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
        std::dynamic_pointer_cast<OpenglShader>(s_Data->FlatColorShader)->bind();
        std::dynamic_pointer_cast<OpenglShader>(s_Data->FlatColorShader)->uploadUniformFloat4("u_Color", color);
        s_Data->QuadVertexArray->bind();
        RenderCommand::drawVertexArray(s_Data->QuadVertexArray);
        glCheckError();
    }
}