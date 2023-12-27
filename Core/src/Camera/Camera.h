#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Events/Events.h"
#include "../Window/Window.h"

#include "../Renderer/Shader.h"

namespace Velkro
{
	class Camera
	{
	public:
		VELKRO_API		Camera();
		VELKRO_API		~Camera();

		VELKRO_API		void UpdateEvents(Event& event, Window& window);
		VELKRO_API		void UpdateMatrices(Shader& shader, glm::vec2 viewportScale);

	private:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

		bool m_FirstMousePress = true;
		
		float m_Speed = 0.01f;

		float m_FOV = 90.0f;

		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;

		glm::vec2 m_OldMousePos;

		float m_MouseSensitivity = 0.1f;
	};
}
