#include "pch.h"
#include "ConstantVariable.h"

void ConstantVariable::PostUniform(GLuint ShaderProgram) const
{
	viewTransform.PostUniform(ShaderProgram);
	projTransform.PostUniform(ShaderProgram);
	lightPosition.PostUniform(ShaderProgram);
	lightColor.PostUniform(ShaderProgram);
	lightStrength.PostUniform(ShaderProgram);
	eyePosition.PostUniform(ShaderProgram);
	ambientLight.PostUniform(ShaderProgram);
	textureFirst.PostUniform(ShaderProgram);
	textureSecond.PostUniform(ShaderProgram);
}
