#include "pch.h"
#include "UIRenderItem.h"
#include "framework.h"
#include "Color.h"

UIRenderItem::UIRenderItem(GLuint shaderProgram, VertexArrayObject<2> vao, Texture tex)
	: shaderProgram(shaderProgram), vao(vao)
{
	this->surfaceTexture = tex;
	this->objectColor.variable = Color::Green;
}

UIRenderItem::UIRenderItem(GLuint shaderProgram, VertexArrayObject<2> vao, const std::string& imgDir, FREE_IMAGE_FORMAT format)
	: shaderProgram(shaderProgram), vao(vao)
{
	this->surfaceTexture.Create(imgDir, format, false);
}

void UIRenderItem::Draw()
{
	Framework::GetInstance()->ChangeUIShader(this->shaderProgram);
	this->vao.Bind();
	this->PostUniform();
	glPolygonMode(GL_FRONT_AND_BACK, (this->isLocalWireFramed || this->isGlobalWireFramed) ? (GL_LINE) : (GL_FILL));
	glDrawArrays(GL_TRIANGLES, 0, this->vao.vertex_count);
}

void UIRenderItem::PostUniform() const
{
	this->surfaceTexture.Bind(0);
	this->objectColor.PostUniform(this->shaderProgram);
	this->worldTrasform.PostUniform(this->shaderProgram);
	this->textureTrasform.PostUniform(this->shaderProgram);
}
