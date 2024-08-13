//
// Created by mathe on 12/08/2024.
//

#include "lypch.h"
#include "RenderAPI.h"

namespace Lypo
{
    class RenderCommand
    {
        public:
            static void setClearColor(float r, float g, float b, float a)
            {
                RenderAPI::setClearColor(r, g, b, a);
            }

            static void clear()
            {
                RenderAPI::clear();
            }

            static void drawVertexArray(const std::shared_ptr<VertexArray>& vertexArray)
            {
                RenderAPI::drawVertexArray(vertexArray);
            }
    };
}