//
// Created by lapor on 7/19/2024.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "core/rendering/VertexBuffer.hpp"
#include "core/rendering/IndexBuffer.hpp"
#include "core/rendering/VertexArray.hpp"
#include "core/rendering/BufferUtils.h"
#include "platform/opengl/GLCheck.h"

#include "../../core/events/event_bus.h"
#include "windows_window.h"

#include "core/rendering/VertexBuffer.hpp"
#include "core/rendering/IndexBuffer.hpp"
#include "core/rendering/VertexArray.hpp"
#include "core/rendering/BufferUtils.h"
#include "core/rendering/Texture.h"
#include "core/rendering/shader.h"
#include "core/rendering/Renderer.hpp"

#include "platform/opengl/opengl_shader.h"
#include "platform/opengl/GLCheck.h"

unsigned int createBasicShader();
unsigned int createTextureShader();

int main(void)
{
    /* create a windowed mode window and its OpenGL context */
    platform::WindowsWindow window = platform::WindowsWindow("Windows Window", 600, 700, core::WindowFlags::DEFAULT);

    //from learnopengl.com
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

/*    unsigned int shaderProgram = createBasicShader();
    unsigned int textureShader = createTextureShader();*/


    std::string fragmentPath = "../LypoEngine/assets/shaders/basicColorShader.frag.glsl";
    std::string vertexPath = "../LypoEngine/assets/shaders/basicColorShader.vert.glsl";

    std::shared_ptr<Lypo::OpenglShader> colorShader = std::make_shared<Lypo::OpenglShader>(vertexPath, fragmentPath);

    fragmentPath = "../LypoEngine/assets/shaders/textureShader.frag.glsl";
    vertexPath = "../LypoEngine/assets/shaders/textureShader.vert.glsl";

    auto& bus = Lypo::EventBus::getInstance();

    auto eventHandler1 = new Lypo::RealNode(1);

    auto eventHandler1_1 = new Lypo::RealNode(11);
    auto eventHandler1_2 = new Lypo::RealNode(12);
    auto eventHandler1_3 = new Lypo::RealNode(13);

    auto eventHandler1_1_1 = new Lypo::RealNode(111);
    auto eventHandler1_1_2 = new Lypo::RealNode(112);

    auto eventHandler1_2_1 = new Lypo::RealNode(121);
    auto eventHandler1_2_2 = new Lypo::RealNode(122);


    eventHandler1_1->addChild(eventHandler1_1_1);
    eventHandler1_1->addChild(eventHandler1_1_2);

    eventHandler1_1->addChild(eventHandler1_2_1);
    eventHandler1_1->addChild(eventHandler1_2_2);

    bus.addEventListener(eventHandler1);

    eventHandler1->addChild(eventHandler1_1);
    eventHandler1->addChild(eventHandler1_2);
    eventHandler1->addChild(eventHandler1_3);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Error in glad load" << std::endl;
        return -1;
    }
  
    std::shared_ptr<Lypo::OpenglShader> textureShader = std::make_shared<Lypo::OpenglShader>(vertexPath, fragmentPath);

    std::shared_ptr<Lypo::VertexArray> vertexArray;
    std::shared_ptr<Lypo::VertexArray> squareVA;

    vertexArray.reset(Lypo::VertexArray::create());

    float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    std::shared_ptr<Lypo::VertexBuffer> vertexBuffer = std::shared_ptr<Lypo::VertexBuffer>(Lypo::VertexBuffer::create(vertices, sizeof(vertices)));
    Lypo::BufferLayout layout = {
            { Lypo::ShaderDataType::Float3, "a_Position" },
            { Lypo::ShaderDataType::Float4, "a_Color" }
    };
    vertexBuffer->setLayout(layout);

    vertexArray->addVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };
    std::shared_ptr<Lypo::IndexBuffer> indexBuffer;
    indexBuffer.reset(Lypo::IndexBuffer::create(indices, sizeof(indices)));
    vertexArray->setIndexBuffer(indexBuffer);

    squareVA.reset(Lypo::VertexArray::create());

    float squareVertices[5 * 4] = {
            -0.75f, -0.75f, 0.0f,  0.0f, 0.0f,
            0.75f, -0.75f, 0.0f,  1.0f, 0.0f,
            0.75f,  0.75f, 0.0f,  1.0f, 1.0f,
            -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
    };

    std::shared_ptr<Lypo::VertexBuffer> squareVB = std::shared_ptr<Lypo::VertexBuffer>(Lypo::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
    squareVB->setLayout({
                                {Lypo::ShaderDataType::Float3, "a_Position"},
                                { Lypo::ShaderDataType::Float2, "a_TexCoord" }
                        });
    squareVA->addVertexBuffer(squareVB);
  
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    std::shared_ptr<Lypo::IndexBuffer> squareIB;
    squareIB.reset(Lypo::IndexBuffer::create(squareIndices, sizeof(squareIndices)));
    squareVA->setIndexBuffer(squareIB);

    std::shared_ptr<Lypo::Texture2D> m_Texture = Lypo::Texture2D::Create("../LypoEngine/assets/textures/Checkerboard.png");

    textureShader->bind();
    textureShader->uploadUniformInt("u_Texture", 0);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(window.getNativeWindow())))
    {

        Lypo::Renderer::beginScene();

        m_Texture->bind();
        Lypo::Renderer::submitGeometryToDraw(squareVA, textureShader);

        Lypo::Renderer::submitGeometryToDraw(vertexArray, colorShader);

        Lypo::Renderer::endScene();

        /* Poll for and process events */
        window.onUpdate();
      
        /* Simple test to query if a specific key is pressed */
        // std::cout << im.isKeyPressed(68) << std::endl;
    }
    return 0;
}