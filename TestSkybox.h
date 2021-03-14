#pragma once
#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test {

	class TestSkybox : public Test
	{
	public:
		TestSkybox();
		~TestSkybox();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::string m_Skyboxpath = "res/textures/skybox";

		// Rendering 
		std::unique_ptr<VertexArray> m_SkyboxVAO;
		std::unique_ptr<VertexBuffer> m_SkyboxVBO;
		std::unique_ptr<Texture> m_CubemapTexture;
		std::unique_ptr<Shader> m_SkyboxShader;

		std::unique_ptr<VertexArray> m_CubeVAO;
		std::unique_ptr<VertexBuffer> m_CubeVBO;
		std::unique_ptr<Texture> m_CubeTexture;
		std::unique_ptr<Shader> m_CubeShader;


		glm::mat4 m_Proj, m_View;
		glm::mat4 m_Model;
		float m_CubeRotationXYZ = 0.0f;
		float m_Cam_Z_Rotation = 0.0f;
		glm::vec3 cube_transform = { 0.0f,0.0f,0.0f };
		glm::vec3 cam_transform = { 0.0f,0.0f,-10.0f };
		glm::vec3 skybox_transform = { 0.0f,0.0f,0.0f };

	};

}
