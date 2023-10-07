#include "ShaderLoader.hpp"
#include "glad/glad.h"
#include <iostream>

using namespace Engine::Graphics;

unsigned int ShaderLoader::Load(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	unsigned int result = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vertexShaderSource, nullptr);
	glShaderSource(fs, 1, &fragmentShaderSource, nullptr);

	glCompileShader(vs);
	if (!Check(vs, GL_VERTEX_SHADER))
		return 0U;
	glCompileShader(fs);
	if (!Check(fs, GL_FRAGMENT_SHADER))
		return 0U;

	glAttachShader(result, vs);
	glAttachShader(result, fs);

	glLinkProgram(result);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return result;
}

bool ShaderLoader::Check(unsigned int shader, unsigned int type)
{
	int compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		int messageLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
		messageLength++;
		char* message = new char[messageLength + 1];
		glGetShaderInfoLog(shader, messageLength, &messageLength, message);
		message[messageLength - 1] = '\n';
		message[messageLength] = '\0';
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : type == GL_FRAGMENT_SHADER ? "Fragment" : "Unknown") << " Shader!\n";
		std::cout << message;
		delete[] message;
		glDeleteShader(shader);
		return false;
	}
	return true;
}
