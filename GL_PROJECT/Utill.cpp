#include "pch.h"
#include "Utill.h"
#include "GL_HEADER.h"

void GlPosToWinPos(int size_x, int size_y, int& x, int& y)
{
	x += size_x / 2;
	y = size_y / 2 + y;
}

void WinPosToGlPos(int size_x, int size_y, int& x, int& y)
{
	x -= size_x / 2;
	y = size_y / 2 - y;
}

std::pair<int, int> GlPosToWinPosPair(int size_x, int size_y, int x, int y)
{
	x += size_x / 2;
	y = size_y / 2 + y;
	return std::make_pair(x, y);
}

std::pair<int, int> WinPosToGlPosPair(int size_x, int size_y, int x, int y)
{
	x -= size_x / 2;
	y = size_y / 2 - y;
	return std::make_pair(x, y);
}

GLuint CreateShaderProgram(const char* vsDir, const char* fsDir)
{
	auto VS = LoadShaderObject(vsDir, GL_VERTEX_SHADER);
	auto FS = LoadShaderObject(fsDir, GL_FRAGMENT_SHADER);
	
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, VS);
	glAttachShader(shaderProgram, FS);

	glLinkProgram(shaderProgram);

	glDeleteShader(VS);
	glDeleteShader(FS);

	GLint result;
	GLchar errorLog[ERROR_LOG_SIZE];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, ERROR_LOG_SIZE, NULL, errorLog);
		std::cerr << "ERROR : shaderProgram Failed to Link" << "\n" << errorLog << std::endl;
		return false;
	}
	else
	{
		return shaderProgram;
	}
}

GLuint LoadShaderObject(const char* dir, GLenum shaderType)
{
	std::ifstream ifs(dir);
	std::string data;
	GLuint result = -1;
	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			std::string _line;
			std::getline(ifs, _line);
			data.append(_line);
			data.append("\n");
		}
		result = ComplieShaderObject(data.c_str(), shaderType);
	}
	ifs.close();
	return result;
}

GLuint ComplieShaderObject(const GLchar* data, GLenum shaderType)
{
	GLuint shaderObeject = glCreateShader(shaderType);
	glShaderSource(shaderObeject, 1, &data, NULL);
	glCompileShader(shaderObeject);

	GLint result;
	GLchar errorLog[ERROR_LOG_SIZE];
	glGetShaderiv(shaderObeject, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shaderObeject, ERROR_LOG_SIZE, NULL, errorLog);
		std::cerr << "ERROR : shaderObject Failed to Complie" << "\n" << errorLog << std::endl;
		return false;
	}
	else
	{
		return shaderObeject;
	}
}
