#pragma once
#include "ShaderBase.hpp"
#include "Utilities/Transform.hpp"
#include "Graphics/DirectionalLight.hpp"

// class WorldShader
//
// Purpose: Abstracted high-level interface for the World Shader in GLSL.

namespace Engine::Graphics
{
	class Camera;
	class Material;
	class WorldShader : public ShaderBase
	{
	public:
		Camera* pCamera;
		DirectionalLight* pDirectionalLight;
		WorldShader();
		~WorldShader() override;
		void Load(const char* vertexShaderSource, const char* fragmentShaderSource) override;
		void Use() override;
		void SetModel(const Utilities::Transform& modelTransform);
		void SetMaterial(const Material& material);
		bool IsDynamic();
	private: // Private static
		static GLuint s_loadedInstances;
		static GLuint s_uboDirectionalLight;
		static GLuint s_uboMaterial;
		static void InitUniformBuffers();
		static void CleanupUniformBuffers();
	private: // Private non-static
		GLint m_uCameraPosition;
		GLint m_uProjView;
		GLint m_uModel;
		DirectionalLight m_lastDirLight; // Used for comparations only
		void UpdateDirectionalLight(DirectionalLight& dl);
	};
}