#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Engine::Core {

	class Camera {

	public:

		Camera();
		Camera(glm::vec3 m_Position, glm::vec3 m_Forward, glm::vec3 m_Right, glm::vec3 m_Up);
		void UpdateProjectionMatrix(float fov, float width, float height, float nearPlane, float farPlane);
		void UpdateViewMatrix();
		void CalculateDirection();

		void SetPosition(const glm::vec3& position) { m_Position = position; }
		void SetForward(const glm::vec3& forward) { m_Forward = forward; }
		void SetRight(const glm::vec3& right) { m_Right = right; }
		void SetUp(const glm::vec3& up) { m_Up = up; }
		void SetYaw(float yaw) { m_yaw = yaw; }
		void SetPitch(float pitch) { m_pitch = pitch; }
		void SetSpeed(float speed) { m_Speed = speed; }
		void SetFov(float fov) { m_fov = fov; }
		void SetNearPlane(float nearPlane) { m_nearPlane = nearPlane; }
		void SetFarPlane(float farPlane) { m_farPlane = farPlane; }
		void SetViewMatrix(const glm::mat4& viewMatrix) { m_ViewMatrix = viewMatrix; }



		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec3 GetForward() const { return m_Forward; }
		glm::vec3 GetRight() const { return m_Right; }
		glm::vec3 GetUp() const { return m_Up; }
		float GetYaw() const { return m_yaw; }
		float GetPitch() const { return m_pitch; }
		float GetSpeed() const { return m_Speed; }
		float GetFov() const { return m_fov; }
		float GetNearPlane() const { return m_nearPlane; }
		float GetFarPlane() const { return m_farPlane; }
		glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		glm::mat4 GetProjectionMatrix() const { return m_Projection; }


		
	private:
		
		float m_Speed = 0.0f;
		float m_yaw = -90.0f;
		float m_pitch = 0.0f;

		float m_fov = 45.0f;
		float m_nearPlane = 0.1f;
		float m_farPlane = 100.0f;
		

		glm::vec3 m_Right;
		glm::vec3 m_Up;
		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position;
		glm::vec3 m_Forward;
		glm::mat4 m_Projection;
		
	};

}