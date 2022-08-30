#include "pch.h"
#include "RenderItem.h"
#include "Material.h"
#include "framework.h"


RenderItem::RenderItem(GLuint shaderProgram, VertexArrayObject<4> vao, Material* material)
	: vao(vao), material(material)
{
	this->shaderProgram = shaderProgram;
}

void RenderItem::Draw()
{
	Framework::GetInstance()->ChangeShader(this->shaderProgram);
	this->vao.Bind();
	this->PostUniform();
	(this->isGlobalTwoSide || this->isLocalTwoSide) ? (glDisable(GL_CULL_FACE)) : (glEnable(GL_CULL_FACE));
	glPolygonMode(GL_FRONT_AND_BACK, (this->isLocalWireFramed || this->isGlobalWireFramed) ? (GL_LINE) : (GL_FILL));
	glDrawArrays(this->drawType, 0, this->vao.vertex_count);
}

void RenderItem::PostUniform() const
{
	this->material->PostUniform(this->shaderProgram);
	this->objectColor.PostUniform(this->shaderProgram);
	this->worldTrasform.PostUniform(this->shaderProgram);
	this->textureTrasform.PostUniform(this->shaderProgram);
}
