#include <glad/glad.h>
#include "Graphics/Renderer.hpp"

using namespace Engine::Graphics;
using namespace Engine::Utilities;

Vector2 Renderer::windowSize = Vector2();
MeshList Renderer::s_dynamicMeshes = MeshList();
MeshList Renderer::s_staticMeshes = MeshList();

void Renderer::Init(size_t arraySize)
{
	const char* vs_dynamic = R"(
#version 330 core

layout(location = 0) in vec3 v_in_pos;
layout(location = 1) in vec3 v_in_nor;
layout(location = 2) in vec2 v_in_uv;

out vec3 v_out_pos;
out vec3 v_out_nor;
out vec2 v_out_uv;

uniform mat4 u_projView;
uniform mat4 u_model;

void main()
{
	gl_Position = u_projView * u_model * vec4(v_in_pos, 1.0);

	v_out_pos = vec3(u_model * vec4(v_in_pos, 1.0));
	v_out_nor = mat3(transpose(inverse(u_model))) * v_in_nor;
	v_out_uv = v_in_uv;
}
)";

	const char* fs_dynamic = R"(
#version 330 core

in vec3 v_out_pos;
in vec3 v_out_nor;
in vec2 v_out_uv;

out vec4 f_color;

uniform vec3 u_cameraPosition;

layout(std140) uniform ubo_directionalLight
{
	vec3 u_directionalAmbient;
	vec3 u_directionalColor;
	vec3 u_directionalDirection;
};

layout(std140) uniform ubo_material
{
	bool u_diffuseEnabled;
	bool u_specularEnabled;
	bool u_emissionEnabled;
	vec3 u_diffuseColor;
	vec3 u_specularColor;
	vec3 u_emissionColor;
};

uniform struct Textures
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
} u_textures;

vec3 CalculateSpecular(vec3 specularColor, vec3 normal)
{
	vec3 viewDirection = normalize(u_cameraPosition - v_out_pos);
	vec3 reflectDirection = reflect(-u_directionalDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
	vec3 specularFrag = specularColor * specularAmount / 2.0;
	return specularFrag;
}

void main()
{
	// Pre-calculations
	vec3 normalizedNormal = normalize(v_out_nor);

	// Diffuse fragment
	vec3 diffuseFrag;
	if (u_diffuseEnabled)
		diffuseFrag = texture(u_textures.diffuse, v_out_uv).rgb * u_diffuseColor;
	else
		diffuseFrag = u_diffuseColor;

	// Unshaded color
	vec3 frag;

	// Ambient
	frag = u_directionalAmbient * diffuseFrag;

	// Diffuse lighting
	frag += max(0.0, dot(u_directionalDirection, normalizedNormal)) * u_directionalColor * diffuseFrag;

	if (u_specularEnabled)
		frag += CalculateSpecular(texture(u_textures.specular, v_out_uv).rgb * u_specularColor, normalizedNormal);
	else
		frag += CalculateSpecular(u_specularColor, normalizedNormal);

	// Emission
	if (u_emissionEnabled)
		frag += texture(u_textures.emission, v_out_uv).rgb * u_emissionColor;
	else
		frag += u_emissionColor;

	// Final
	f_color = vec4(frag, 1.0);
}
)";

	const char* vs_static = R"(
#version 330 core

layout(location = 0) in vec3 v_in_pos;
layout(location = 1) in vec3 v_in_nor;
layout(location = 2) in vec2 v_in_uv;

out vec3 v_out_pos;
out vec3 v_out_nor;
out vec2 v_out_uv;

uniform mat4 u_projView;

void main()
{
	gl_Position = u_projView * vec4(v_in_pos, 1.0);

	v_out_pos = v_in_pos;
	v_out_nor = v_in_nor;
	v_out_uv = v_in_uv;
}
)";

	const char* fs_static = R"(
#version 330 core

in vec3 v_out_pos;
in vec3 v_out_nor;
in vec2 v_out_uv;

out vec4 f_color;

layout(std140) uniform ubo_directionalLight
{
	vec3 u_directionalAmbient;
	vec3 u_directionalColor;
	vec3 u_directionalDirection;
};

layout(std140) uniform ubo_material
{
	bool u_diffuseEnabled;
	vec3 u_diffuseColor;
};

uniform struct Textures
{
	sampler2D diffuse;
} u_textures;

void main()
{
	// Unshaded color
	vec3 frag;
	if (u_diffuseEnabled)
		frag = texture(u_textures.diffuse, v_out_uv).rgb * u_diffuseColor;
	else
		frag = u_diffuseColor;

	// Ambient and diffuse
	vec3 lightAmount = max(0.0, dot(u_directionalDirection, v_out_nor)) * u_directionalColor;
	frag *= u_directionalAmbient + lightAmount;

	// Final
	f_color = vec4(frag, 1.0);
}
)";

	s_dynamicMeshes.Init(arraySize);
	s_dynamicMeshes.shader.Load(vs_dynamic, fs_dynamic);
	s_staticMeshes.Init(arraySize);
	s_staticMeshes.shader.Load(vs_static, fs_static);

}

void Renderer::RenderAll()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	s_dynamicMeshes.RenderAll();
	s_staticMeshes.RenderAll();
}

unsigned int Renderer::AddMesh(bool isDynamic, Mesh* pMesh)
{
	if (isDynamic)
		return s_dynamicMeshes.AddMesh(pMesh);
	else
		return s_staticMeshes.AddMesh(pMesh);
}

void Renderer::SetMesh(bool isDynamic, unsigned int index, Mesh* pMesh)
{
	if (isDynamic)
		s_dynamicMeshes.SetMesh(index, pMesh);
	else
		s_staticMeshes.SetMesh(index, pMesh);
}

void Renderer::RemoveMesh(bool isDynamic, unsigned int index)
{
	if (isDynamic)
		s_dynamicMeshes.RemoveMesh(index);
	else
		s_staticMeshes.RemoveMesh(index);
}
