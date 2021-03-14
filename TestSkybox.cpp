#include "TestSkybox.h"

#include <iostream>

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	static float s_skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	std::vector<std::string> s_faces = {
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
	};

	static float s_CubeVertices[] = {
		// positions          // texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	TestSkybox::TestSkybox()
		:m_Proj(glm::perspective(glm::radians(45.0f), (float) 1900/980, 0.1f, 1000.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -10.0f))),
		m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
	{
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);
	/*	glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);*/

		//Cube
		m_CubeVAO = std::make_unique<VertexArray>();
		m_CubeVBO = std::make_unique<VertexBuffer>(s_CubeVertices, 36 * 5 * sizeof(float));
		VertexBufferLayout cubelayout;
		cubelayout.Push<float>(3);
		cubelayout.Push<float>(2);
		m_CubeVAO->AddBuffer(*m_CubeVBO, cubelayout);
		
		m_CubeTexture = std::make_unique<Texture>("res/textures/wall.jpg");
		m_CubeTexture->Bind(1);

		m_CubeShader = std::make_unique<Shader>("res/shaders/CubeDefault.shader");
		m_CubeShader->Bind();
		m_CubeShader->SetUniform1i("u_Texture", 1);
		m_CubeShader->Unbind();


		//Skybox
		m_SkyboxVAO = std::make_unique<VertexArray>();
		m_SkyboxVBO = std::make_unique<VertexBuffer>(s_skyboxVertices, 36 * 3 * sizeof(float));
		VertexBufferLayout skyboxlayout;
		skyboxlayout.Push<float>(3);
		m_SkyboxVAO->AddBuffer(*m_SkyboxVBO, skyboxlayout);
		/*unsigned int indices[36];
		for (unsigned int i = 0; i < 36; i++)
			indices[i] = i;
		m_IBO = std::make_unique<IndexBuffer>(indices,36);*/

		m_CubemapTexture = std::make_unique<Texture>(m_Skyboxpath,s_faces);
		//m_CubemapTexture = std::make_unique<Texture>(m_Skyboxpath,"pink_sunrise_4k.hdr");
		m_CubemapTexture->BindCubemap(2);
		m_SkyboxShader = std::make_unique<Shader>("res/shaders/Skybox.shader");
		m_SkyboxShader->Bind();
		m_SkyboxShader->SetUniform1i("u_skybox", 2);
		m_SkyboxShader->Unbind();
	}

	TestSkybox::~TestSkybox()
	{

	}

	void TestSkybox::OnUpdate(float deltaTime)
	{
		m_Cam_Z_Rotation += 1.0f * deltaTime;
		m_View = glm::translate(glm::mat4(1.0f), cam_transform) * glm::rotate(glm::mat4(1.0f),glm::radians(m_Cam_Z_Rotation),glm::vec3(0.0f,1.0f,0.0f));
		
		m_Model = glm::translate(glm::mat4(1.0f), cube_transform);
		m_CubeRotationXYZ += 2.8f * deltaTime;
		m_Model = glm::rotate(m_Model, glm::radians(m_CubeRotationXYZ), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void TestSkybox::OnRender()
	{
		GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Renderer renderer;


		// Cube rendering 
		{
			m_CubeShader->Bind();
			//m_CubeTexture->Bind(1);

			glm::mat4 model = glm::translate(glm::mat4(1.0f), cube_transform);
			glm::mat4 mvp = m_Proj * m_View * m_Model;
			m_CubeShader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_CubeVAO, 36, *m_CubeShader);
			m_CubeShader->Unbind();
		}



		// skybox rendering 
		{
			glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
			m_SkyboxShader->Bind();
			//m_CubemapTexture->BindCubemap(2);

			m_View = glm::mat4(glm::mat3(m_View)); // prevent the skybox from translating based on the camera translation
			glm::mat4 model = glm::translate(glm::mat4(1.0f), skybox_transform);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_SkyboxShader->SetUniformMat4f("u_MVP", mvp);

			//glDepthMask(GL_FALSE);
			renderer.Draw(*m_SkyboxVAO, 36, *m_SkyboxShader);
			//glDepthMask(GL_TRUE);
			m_SkyboxShader->Unbind();

			glDepthFunc(GL_LESS); // set depth function back to default

		}
	}

	void TestSkybox::OnImGuiRender()
	{

		// Debug
		ImGui::Begin("Skybox Debug");
		{
			ImGui::DragFloat3("Cam Translate: ", &cam_transform.x, 0.1f);
			ImGui::Separator();
			ImGui::DragFloat("Cube XYZ rotation:",&m_CubeRotationXYZ,0.1f);
			ImGui::Separator();
			ImGui::DragFloat3("Cube Translate: ", &cube_transform.x, 0.1f);
			ImGui::Separator();
			ImGui::DragFloat3("skybox Translate: ", &skybox_transform.x, 0.1f);

			ImGui::End();
		}
	}
}
