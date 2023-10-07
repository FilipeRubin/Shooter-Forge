#include "ShaderBase.hpp"

using namespace Engine::Graphics;

ShaderBase::ShaderBase()
	:m_program(0U)
{
}

ShaderBase::~ShaderBase()
{
	Unload();
}

void ShaderBase::Unload()
{
	if (m_program != 0U)
	{
		glDeleteProgram(m_program);
		m_program = 0U;
	}
}