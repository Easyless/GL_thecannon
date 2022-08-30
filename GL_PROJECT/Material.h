#pragma once
#include <array>
#include "UniformVariable.h"
#include "GL_HEADER.h"
#include "MacroDefined.h"
#include "Texture.h"

struct Material
{
	UniformVariable<glm::vec4> diffuseAlbedo = UniformVariable<glm::vec4>("diffuseAlbedo", glm::vec4(1.0f));
	UniformVariable<GLint> shininess = UniformVariable<GLint>("shininess", 12);

	UniformVariable<glm::vec4> emissive = UniformVariable<glm::vec4>("emissiveColor", glm::vec4(0.0f));
	UniformVariable<glm::vec4> ambient = UniformVariable<glm::vec4>("ambientColor", glm::vec4(0.0f));
	UniformVariable<GLfloat> lightAffect = UniformVariable<GLfloat>("lightAffect", 1.0f);

	std::array<Texture, TEXTURE_MAX> textures;

	//아직 사용 안함
	UniformVariable<glm::vec3> fresnelR0 = UniformVariable<glm::vec3>("fresnelR0", glm::vec3(0.1f));
	UniformVariable<GLfloat> roughness = UniformVariable<GLfloat>("roughness", 0.25f);
	
	void AddTexture(size_t index, Texture tex)
	{
		this->textures[index] = tex;
	}

	void PostUniform(GLuint ShaderProgram) const
	{
		this->diffuseAlbedo.PostUniform(ShaderProgram);
		this->shininess.PostUniform(ShaderProgram);

		this->emissive.PostUniform(ShaderProgram);
		this->ambient.PostUniform(ShaderProgram);
		this->lightAffect.PostUniform(ShaderProgram);

		this->fresnelR0.PostUniform(ShaderProgram);
		this->roughness.PostUniform(ShaderProgram);

		for (size_t i = 0; i < this->textures.size(); i++)
		{
			this->textures[i].Bind(i);
		}
	}
};