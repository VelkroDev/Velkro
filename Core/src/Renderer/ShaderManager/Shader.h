#pragma once

#include <glad/glad.h>

#include "../../FileManager/FileInput.h"

namespace Velkro
{
	class Shader
	{
	public:
		Shader(uint32_t rendererID)
			: m_RendererID(rendererID)
		{
		}

		Shader()
		{
		}

		static Shader CreateShaderFromFile(const char* vertexShaderPath, const char* fragShaderPath)
		{
			FileInput vertexInput = FileInput::CreateFileInput(vertexShaderPath);

			std::string vertexShaderStr = vertexInput.GetInput();
			const char* vertexShaderSource = vertexShaderStr.c_str();

			FileInput fragInput = FileInput::CreateFileInput(fragShaderPath);

			std::string fragShaderStr = fragInput.GetInput();
			const char* fragShaderSource = fragShaderStr.c_str();

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

			glCompileShader(vertexShader);

			int success;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				VLK_CORE_INFO("Vertex shader compilation failed: {}", infoLog);
			}

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);

			glCompileShader(fragmentShader);

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				VLK_CORE_INFO("Fragment shader compilation failed: {}", infoLog);
			}

			GLuint shaderProgram = glCreateProgram();

			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);

			glLinkProgram(shaderProgram);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return Shader(shaderProgram);
		}

		static Shader CreateShaderFromData(const char* vertexShaderSource, const char* fragShaderSource)
		{
			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

			glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

			glCompileShader(vertexShader);

			int success;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				VLK_CORE_INFO("Vertex shader compilation failed: {}", infoLog);
			}

			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);

			glCompileShader(fragmentShader);

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				char infoLog[512];
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				VLK_CORE_INFO("Fragment shader compilation failed: {}", infoLog);
			}

			GLuint shaderProgram = glCreateProgram();

			glAttachShader(shaderProgram, vertexShader);
			glAttachShader(shaderProgram, fragmentShader);

			glLinkProgram(shaderProgram);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return Shader(shaderProgram);
		}

		void Bind()
		{
			glUseProgram(m_RendererID);
		}

		void UnBind()
		{
			glUseProgram(0);
		}

		uint32_t GetRendererID()
		{
			return m_RendererID;
		}

		bool operator==(const Shader& other) const
		{
			return m_RendererID == other.m_RendererID;
		}

	private:
		uint32_t m_RendererID;
	};
}