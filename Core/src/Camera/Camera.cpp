#include <vlkpch.h>

#include "Camera.h"

namespace Velkro
{
	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::UpdateEvents(Event& event, Window& window)
	{
		if (event.GetKeyEvent(VLK_KEY_W) == VLK_PRESS)
		{
			m_Position -= m_Front * m_Speed;
		}
		if (event.GetKeyEvent(VLK_KEY_A) == VLK_PRESS)
		{
			m_Position += glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f))) * m_Speed;
		}
		if (event.GetKeyEvent(VLK_KEY_S) == VLK_PRESS)
		{
			m_Position += m_Front * m_Speed;
		}
		if (event.GetKeyEvent(VLK_KEY_D) == VLK_PRESS)
		{
			m_Position -= glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f))) * m_Speed;
		}

		if (event.GetKeyEvent(VLK_KEY_SPACE) == VLK_PRESS)
		{
			m_Position += m_Up * m_Speed;
		}
		if (event.GetKeyEvent(VLK_KEY_LEFT_SHIFT) == VLK_PRESS)
		{
			m_Position -= m_Up * m_Speed;
		}
		if (event.GetMouseButtonEvent(VLK_MOUSE_BUTTON_RIGHT) == VLK_PRESS)
		{
			if (m_FirstMousePress == true)
			{
				window.SetMouseVisibility(false);

				m_OldMousePos = window.GetMousePos();
				m_FirstMousePress = false;
			}

			glm::vec2 mousePos = window.GetMousePos();

			float xOffset = mousePos.x - m_OldMousePos.x;
			float yOffset = m_OldMousePos.y - mousePos.y;
			m_OldMousePos = mousePos;

			m_Yaw += xOffset * m_MouseSensitivity;
			m_Pitch -= yOffset * m_MouseSensitivity;

			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;

			glm::vec3 newFront;
			newFront.x = static_cast<float>(cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));
			newFront.y = static_cast<float>(sin(glm::radians(m_Pitch)));
			newFront.z = static_cast<float>(sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));

			m_Front = glm::normalize(newFront);
		}
		else if (event.GetMouseButtonEvent(VLK_MOUSE_BUTTON_RIGHT) == VLK_RELEASE)
		{
			window.SetMouseVisibility(true);

			m_FirstMousePress = true;
		}
	}

	void Camera::UpdateMatrices(Shader& shader, Window& window)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), float(window.GetWidth() / window.GetHeight()), 0.001f, 100.0f);
		m_ViewMatrix = glm::lookAt(m_Position, m_Position - m_Front, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 camMatrix = m_ProjectionMatrix * m_ViewMatrix;

		glUniform3f(glGetUniformLocation(shader.GetRendererID(), "u_CameraPos"), m_Position.x, m_Position.y, m_Position.z);
		glUniformMatrix4fv(glGetUniformLocation(shader.GetRendererID(), "u_CameraMatrix"), 1, false, glm::value_ptr(camMatrix));
	}
}