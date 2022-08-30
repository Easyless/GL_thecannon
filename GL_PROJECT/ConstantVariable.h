#pragma once
#include "GL_HEADER.h"
#include "MacroDefined.h"
#include "UniformVariable.h"
#include "Utill.h"
#include <array>
struct ConstantVariable
{
	UniformVariable<glm::mat4> viewTransform = UniformVariable<glm::mat4>("viewTransform", glm::mat4(1.0f));
	UniformVariable<glm::mat4> projTransform = UniformVariable<glm::mat4>("projTransform", glm::mat4(1.0f));
	UniformVariable<glm::vec4> eyePosition = UniformVariable<glm::vec4>("eyePosition", glm::vec4(1.0f));

	UniformVariable<glm::vec4> ambientLight = UniformVariable<glm::vec4>("ambientLight", glm::vec4(0.0f));

	UniformVariable<std::array<glm::vec4, LIGHT_MAX>> lightPosition = 
		UniformVariable<std::array<glm::vec4, LIGHT_MAX>>("lightPosition", FilledArray<glm::vec4,LIGHT_MAX>(glm::vec4(0.0f)));
	UniformVariable<std::array<glm::vec4, LIGHT_MAX>> lightColor =
		UniformVariable<std::array<glm::vec4, LIGHT_MAX>>("lightColor", FilledArray<glm::vec4, LIGHT_MAX>(glm::vec4(1.0f)));
	UniformVariable<std::array<GLfloat, LIGHT_MAX>> lightStrength = 
		UniformVariable<std::array<GLfloat, LIGHT_MAX>>("lightStrength", FilledArray<GLfloat, LIGHT_MAX>(0.0f));

	UniformVariable<GLint> textureFirst = UniformVariable<GLint>("textureFirst", 0);
	UniformVariable<GLint> textureSecond = UniformVariable<GLint>("textureSecond", 1);


	//UniformVariable<glm::vec4> lightPosition = UniformVariable<glm::vec4>("lightPosition", glm::vec4(0.0f, 2.5f, 0.0f, 1.0f));
	//UniformVariable<glm::vec4> lightColor = UniformVariable<glm::vec4>("lightColor", glm::vec4(1.0f));
	//UniformVariable<GLfloat> lightStrength = UniformVariable<GLfloat>("lightStrength", 0.0f);

	void PostUniform(GLuint ShaderProgram) const;
};
