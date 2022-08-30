#pragma once
#include "GL_HEADER.h"
#include "MacroDefined.h"
#include <string>
#include <array>

template<typename Ty>
struct PostFunctionSet
{
	static void Func(GLint location, const Ty& variable)
	{
		static_assert(0, "This type's Post Function should be declared");
	}
};


template<>
static void PostFunctionSet<glm::vec3>::Func(GLint location, const glm::vec3& variable)
{
	glUniform4fv(location, 1, glm::value_ptr(variable));
}

template<>
static void PostFunctionSet<std::array<glm::vec3, LIGHT_MAX>>::Func(GLint location, const std::array<glm::vec3, LIGHT_MAX>& variable)
{
	glUniform3fv(location, LIGHT_MAX, glm::value_ptr(variable[0]));
}

template<>
static void PostFunctionSet<glm::vec4>::Func(GLint location, const glm::vec4& variable)
{
	glUniform4fv(location, 1, glm::value_ptr(variable));
}

template<>
static void PostFunctionSet<std::array<glm::vec4,LIGHT_MAX>>::Func(GLint location, const std::array<glm::vec4, LIGHT_MAX>& variable)
{
	glUniform4fv(location, LIGHT_MAX, glm::value_ptr(variable[0]));
}


template<>
static void PostFunctionSet<GLint>::Func(GLint location, const GLint& variable)
{
	glUniform1i(location, variable);
}
template<>
static void PostFunctionSet<std::array<GLint, LIGHT_MAX>>::Func(GLint location, const std::array<GLint, LIGHT_MAX>& variable)
{
	glUniform1iv(location, LIGHT_MAX, variable.data());
}


template<>
static void PostFunctionSet<GLuint>::Func(GLint location, const GLuint& variable)
{
	glUniform1ui(location, variable);
}
template<>
static void PostFunctionSet<std::array<GLuint, LIGHT_MAX>>::Func(GLint location, const std::array<GLuint, LIGHT_MAX>& variable)
{
	glUniform1uiv(location,LIGHT_MAX,variable.data());
}


template<>
static void PostFunctionSet<GLfloat>::Func(GLint location, const GLfloat& variable)
{
	glUniform1f(location, variable);
}

template<>
static void PostFunctionSet<std::array<GLfloat, LIGHT_MAX>>::Func(GLint location, const std::array<GLfloat, LIGHT_MAX>& variable)
{
	glUniform1fv(location, LIGHT_MAX, variable.data());
}

template<>
static void PostFunctionSet<glm::mat4>::Func(GLint location, const glm::mat4& variable)
{
	glUniformMatrix4fv(location , 1, GL_FALSE, glm::value_ptr(variable));
}

template<>
static void PostFunctionSet<std::array<glm::mat4, LIGHT_MAX>>::Func(GLint location, const std::array<glm::mat4, LIGHT_MAX>& variable)
{
	glUniformMatrix4fv(location, LIGHT_MAX, GL_FALSE, glm::value_ptr(variable[0]));
}

template<typename Ty, typename PostFunc = PostFunctionSet<Ty>>
struct UniformVariable
{
	Ty variable;
	std::string name;

	UniformVariable(const std::string& name, Ty first)
		:variable(first)
	{
		this->name = name;
	}
	Ty& operator=(const Ty& other)
	{
		this->variable = other;
		return this->variable;
	}
	Ty& operator=(Ty&& other)
	{
		this->variable = std::move(other);
		return this->variable;
	}

	void PostUniform(GLuint shaderProgram) const
	{
		GLint location = glGetUniformLocation(shaderProgram, name.c_str());
		PostFunc::Func(location, this->variable);
	}
};