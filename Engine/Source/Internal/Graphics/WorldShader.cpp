#include "WorldShader.hpp"
#include "ShaderLoader.hpp"
#include "Graphics/Camera.hpp"
#include "Graphics/DirectionalLight.hpp"
#include "Graphics/Material.hpp"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Utilities/TransformUtilities.hpp"

#define TO_GLM_VEC3(x) (*((glm::vec3*)&x))

using namespace Engine::Graphics;
using namespace Engine::Utilities;

GLuint WorldShader::s_loadedInstances = 0U;
GLuint WorldShader::s_uboDirectionalLight = 0U;
GLuint WorldShader::s_uboMaterial = 0U;

WorldShader::WorldShader() :
	pCamera(nullptr),
	pDirectionalLight(nullptr),
	m_uProjView(0),
	m_uModel(0)
{
}

WorldShader::~WorldShader()
{
	if (m_program != 0U) // If it's a loaded instance
	{
		s_loadedInstances--;

		if (s_loadedInstances == 0U)
		{
			CleanupUniformBuffers();
		}
	}
}

void WorldShader::Load(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	if (m_program == 0U)
	{
		s_loadedInstances++;

		if (s_loadedInstances == 1U) // If first loaded instance
		{
			InitUniformBuffers();
		}
	}
	
	Unload();

	m_program = ShaderLoader::Load(vertexShaderSource, fragmentShaderSource);

	const GLuint directionalLightIndex = glGetUniformBlockIndex(m_program, "ubo_directionalLight");
	glUniformBlockBinding(m_program, directionalLightIndex, 0U);

	const GLuint materialIndex = glGetUniformBlockIndex(m_program, "ubo_material");
	glUniformBlockBinding(m_program, materialIndex, 1U);

	// Texture unit set
	glUseProgram(m_program);
	glUniform1i(glGetUniformLocation(m_program, "u_textures.diffuse"), 0);

	m_uProjView = glGetUniformLocation(m_program, "u_projView");
	m_uModel = glGetUniformLocation(m_program, "u_model");
}

void WorldShader::Use()
{
	glUseProgram(m_program);

	// Checks which directional light (dl) it should use, and then compare it to the one from the previous frame to see whether it should be updated or not
	DirectionalLight& dl = pDirectionalLight == nullptr ? *DirectionalLight::pCurrentDirectionalLight : *pDirectionalLight;
	if (m_lastDirLight != dl)
		UpdateDirectionalLight(dl);

	// Projection and view matrices
	const Camera& cam = pCamera == nullptr ? *Camera::pCurrentCamera : *pCamera;
	glm::mat4 proj = glm::perspective(glm::radians(cam.fov), cam.aspect, cam.near, cam.far);
	glm::mat4 view = TransformUtilities::GenViewHierarchyMatrix(cam.transform);
	glm::mat4 projView = proj * view;

	glUniformMatrix4fv(m_uProjView, 1, GL_FALSE, &projView[0][0]);
}

void WorldShader::SetModel(const Utilities::Transform& modelTransform)
{
	glm::mat4 model = TransformUtilities::GenWorldHierarchyMatrix(modelTransform);

	glUniformMatrix4fv(m_uModel, 1, GL_FALSE, &model[0][0]);
}

void WorldShader::SetMaterial(const Material& material)
{
	GLint enableDiffuse = material.IsDiffuseEnabled();
	glm::vec3 diffuseColor = glm::vec3(material.diffuseColor.x, material.diffuseColor.y, material.diffuseColor.z);
	
	glBindBuffer(GL_UNIFORM_BUFFER, s_uboMaterial);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(GLint), &enableDiffuse);
	glBufferSubData(GL_UNIFORM_BUFFER, 16, 12U, &diffuseColor);
	if (enableDiffuse)
	{
		material.UseTextures();
	}
}

bool WorldShader::IsDynamic()
{
	return m_uModel != -1;
}

void WorldShader::InitUniformBuffers()
{
	glGenBuffers(1, &s_uboDirectionalLight);
	glBindBuffer(GL_UNIFORM_BUFFER, s_uboDirectionalLight);
	glBufferData(GL_UNIFORM_BUFFER, 48U, nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0U, s_uboDirectionalLight);

	glGenBuffers(1, &s_uboMaterial);
	glBindBuffer(GL_UNIFORM_BUFFER, s_uboMaterial);
	glBufferData(GL_UNIFORM_BUFFER, 32U, nullptr, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1U, s_uboMaterial);
}

void WorldShader::CleanupUniformBuffers()
{
	glDeleteBuffers(1, &s_uboDirectionalLight);
	glDeleteBuffers(1, &s_uboMaterial);
	s_uboDirectionalLight = 0U;
	s_uboMaterial = 0U;
}

void WorldShader::UpdateDirectionalLight(DirectionalLight& dl)
{
	const glm::vec3& ambient = TO_GLM_VEC3(dl.ambient);
	const glm::vec3& color = TO_GLM_VEC3(dl.color);
	const glm::vec3& direction = TO_GLM_VEC3(dl.direction);
	glBindBuffer(GL_UNIFORM_BUFFER, s_uboDirectionalLight);
	glBufferSubData(GL_UNIFORM_BUFFER, 0U, sizeof(glm::vec3), &ambient);
	glBufferSubData(GL_UNIFORM_BUFFER, 16U, sizeof(glm::vec3), &color);
	glBufferSubData(GL_UNIFORM_BUFFER, 32U, sizeof(glm::vec3), &direction);
	m_lastDirLight = dl;
}
