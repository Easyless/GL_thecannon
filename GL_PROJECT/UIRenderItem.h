#pragma once
#include "GL_HEADER.h"
#include "IDrawable.h"
#include "UniformVariable.h"
#include "VertexArrayObject.h"
#include "Texture.h"
#include "FreeImage.h"

class UIRenderItem : public IDrawable
{
private:
	GLuint shaderProgram = -1;
	VertexArrayObject<2> vao;
public:
	bool isLocalWireFramed = false;
	bool isGlobalWireFramed = false;
	Texture surfaceTexture;
	UniformVariable<glm::vec4> objectColor = UniformVariable<glm::vec4>("objectColor", glm::vec4(1.0f));
	UniformVariable<glm::mat4> worldTrasform = UniformVariable<glm::mat4>("worldTransform", glm::mat4(1.0f));
	UniformVariable<glm::mat4> textureTrasform = UniformVariable<glm::mat4>("textureTrasform", glm::mat4(1.0f));
	UIRenderItem(GLuint shaderProgram, VertexArrayObject<2> vao, Texture tex);
	UIRenderItem(GLuint shaderProgram, VertexArrayObject<2> vao, const std::string& imgDir, FREE_IMAGE_FORMAT format);

	void Draw();
	void PostUniform() const;
};