#pragma once

#include <glad/glad.h>

#include <stb/stb_image.h>

#include <cstdint>

#include "../../ShaderManager/Shader.h"

#include "../Logging/Log.h"

namespace Velkro
{
    enum TextureMipMap
    {
        VLK_NEAREST, VLK_LINEAR
    };

    enum TextureWrap
    {
        VLK_REPEAT, VLK_CLAMP_TO_BORDER, VLK_CLAMP_TO_EDGE
    };

    enum TextureType
    {
        VLK_DIFFUSE, VLK_SPECULAR, VLK_NORMAL
    };

	class Texture
	{
	public:
		VELKRO_API      Texture()
		{
		}

		VELKRO_API      Texture(uint32_t rendererID, GLenum textureDimension, TextureType textureType)
			: m_RendererID(rendererID), m_TextureDimension(textureDimension), m_TextureType(textureType)
		{
		}

		VELKRO_API      ~Texture()
		{
		}

        VELKRO_API      void Bind()
        {
            glBindTexture(m_TextureDimension, m_RendererID);
        }

        VELKRO_API      void UnBind()
        {
            glBindTexture(m_TextureDimension, 0);
        }

        VELKRO_API      void SetTextureUnit(Shader& shader, const char* uniformName, uint32_t unit)
        {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, m_RendererID);

            glUniform1i(glGetUniformLocation(shader.GetRendererID(), uniformName), unit);
        }

        VELKRO_API      TextureType GetTextureType()
        {
            return m_TextureType;
        }

	private:
        TextureType m_TextureType;

		uint32_t m_RendererID;
        uint32_t m_TextureDimension;
	};

	class Texture2D : public Texture
	{
	public:
	    VELKRO_API      static Texture CreateTexture(const char* texturePath, TextureMipMap mipmap, TextureWrap wrap, TextureType textureType)
		{
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            stbi_set_flip_vertically_on_load(true);
            int width, height, nrChannels;
            uint32_t rendererID;

            unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

            glGenTextures(1, &rendererID);
            glBindTexture(GL_TEXTURE_2D, rendererID);

            GLenum glMipMap = GL_NEAREST;
            GLenum glWrap = GL_REPEAT;

            switch (mipmap)
            {
                case VLK_NEAREST:
                {
                    glMipMap = GL_NEAREST;

                    break;
                }
                case VLK_LINEAR:
                {
                    glMipMap = GL_LINEAR;

                    break;
                }
            }

            switch (wrap)
            {
                case VLK_REPEAT:
                {
                    glWrap = GL_REPEAT;

                    break;
                }
                case VLK_CLAMP_TO_BORDER:
                {
                    glWrap = GL_CLAMP_TO_BORDER;

                    break;
                }
                case VLK_CLAMP_TO_EDGE:
                {
                    glWrap = GL_CLAMP_TO_EDGE;

                    break;
                }
            }

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glMipMap);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glMipMap);

            if (data)
            {
                GLenum format = 1;
                if (nrChannels == 1)
                    format = GL_RED;
                if (nrChannels == 2)
                    format = GL_RG;
                else if (nrChannels == 3)
                    format = GL_RGB;
                else if (nrChannels == 4)
                    format = GL_RGBA;

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                VLK_CORE_ERROR("Texture failed to load. Texture path: {0}", texturePath);
            }

            stbi_image_free(data);

            glBindTexture(GL_TEXTURE_2D, 0);

            return Texture(rendererID, GL_TEXTURE_2D, textureType);
		}
	};
}