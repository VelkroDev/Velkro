#pragma once

#include <glad/glad.h>

#include <cstdint>

namespace Velkro
{
    class EBO
    {
    public:
        EBO(uint32_t rendererID)
            : m_RendererID(rendererID)
        {
        }
        EBO()
        {
        }

        static EBO CreateEBO(uint32_t* indices, size_t indicesSize)
        {
            uint32_t eboID;
            glGenBuffers(1, &eboID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

            return EBO(eboID);
        }

        void Bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        }

        void UnBind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        uint32_t& GetRendererID()
        {
            return m_RendererID;
        }
    private:
        uint32_t m_RendererID;
    };
}
