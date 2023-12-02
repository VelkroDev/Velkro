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
        ~EBO()
        {
        }

        static EBO CreateEBO()
        {
            uint32_t eboID;

            glGenBuffers(1, &eboID);

            return EBO(eboID);
        }

        void SetData(std::vector<uint32_t> indices, VLK_DATA_USAGE dataUsage = VLK_DYNAMIC)
        {
            GLenum glDataUsage = GL_DYNAMIC_DRAW;

            switch (dataUsage)
            {
                case VLK_DYNAMIC:
                {
                    glDataUsage = GL_DYNAMIC_DRAW;

                    break;
                }
                case VLK_STATIC:
                {
                    glDataUsage = GL_STATIC_DRAW;

                    break;
                }
                case VLK_STREAM:
                {
                    glDataUsage = GL_STREAM_DRAW;

                    break;
                }
                default:
                {
                    VLK_CORE_ERROR("Invalid data usage set for Element Array Buffer. Reverting to VLK_DYNAMIC.");

                    break;
                }
            }

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), glDataUsage);
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
