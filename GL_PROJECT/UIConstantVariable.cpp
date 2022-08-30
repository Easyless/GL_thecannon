#include "pch.h"
#include "UIConstantVariable.h"

void UIConstantVariable::PostUniform(GLuint ShaderProgram) const
{
	viewTransform.PostUniform(ShaderProgram);
	projTransform.PostUniform(ShaderProgram);
	textureFirst.PostUniform(ShaderProgram);
	textureSecond.PostUniform(ShaderProgram);
}
