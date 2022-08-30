#pragma once
#include "GL_HEADER.h"
#include "UniformVariable.h"
#include "VertexArrayObject.h"
#include "Material.h"
#include "IDrawable.h"

class RenderItem : public IDrawable
{
private:
	GLuint shaderProgram = -1;
	VertexArrayObject<4> vao;
public:
	GLenum drawType = GL_POLYGON;
	Material* material = nullptr;
	bool isLocalWireFramed = false;
	bool isGlobalWireFramed = false;
	bool isLocalTwoSide = false;
	bool isGlobalTwoSide = false;
	UniformVariable<glm::vec4> objectColor = UniformVariable<glm::vec4>("objectColor", glm::vec4(1.0f));
	UniformVariable<glm::mat4> worldTrasform = UniformVariable<glm::mat4>("worldTransform", glm::mat4(1.0f));
	UniformVariable<glm::mat4> textureTrasform = UniformVariable<glm::mat4>("textureTrasform", glm::mat4(1.0f));

	RenderItem(GLuint shaderProgram, VertexArrayObject<4> vao, Material* material);

	void Draw();
	void PostUniform() const;
};