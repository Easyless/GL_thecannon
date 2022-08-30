#include "pch.h"
#include "framework.h"
#include "GL_HEADER.h"
#include "Utill.h"
void Framework::BuildShaders()
{
	this->shaderPrograms["default"] = CreateShaderProgram("Shader/vertexShader.glsl", "Shader/pixelShader.glsl");
	this->shaderPrograms["clip"] = CreateShaderProgram("Shader/alphaClippingVertexShader.glsl", "Shader/alphaClippingPixelShader.glsl");
	this->shaderPrograms["skybox"] = CreateShaderProgram("Shader/skyboxVertexShader.glsl", "Shader/skyboxPixelShader.glsl");
	this->shaderPrograms["ui_def"] = CreateShaderProgram("Shader/uiVertexShader.glsl", "Shader/uiPixelShader.glsl");
	this->shaderPrograms["terrain"] = CreateShaderProgram("Shader/terrainVertexShader.glsl", "Shader/terrainPixelShader.glsl");
	this->currentShaderProgram = this->shaderPrograms["default"];

}