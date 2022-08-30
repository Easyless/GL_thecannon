#pragma once
#include "GL_HEADER.h"
#include "MacroDefined.h"
#include "UniformVariable.h"
#include "Utill.h"
#include <array>

struct UIConstantVariable
{
	UniformVariable<glm::mat4> viewTransform = UniformVariable<glm::mat4>("viewTransform", glm::mat4(1.0f));
	UniformVariable<glm::mat4> projTransform = UniformVariable<glm::mat4>("projTransform", glm::mat4(1.0f));

	UniformVariable<GLint> textureFirst = UniformVariable<GLint>("textureFirst", 0);
	UniformVariable<GLint> textureSecond = UniformVariable<GLint>("textureSecond", 1);

	void PostUniform(GLuint ShaderProgram) const;
};
