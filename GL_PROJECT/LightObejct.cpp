#include <assert.h>
#include "pch.h"
#include "LightObejct.h"
#include "framework.h"

size_t LightObject::currentLight = 0;

LightObject::LightObject(Framework* framework, GLuint shaderProgram, const std::string& meshTag, const std::string& materialTag)
	:GameObject(framework, shaderProgram, meshTag, materialTag)
{
	this->lightIndex = LightObject::currentLight;
	assert(this->lightIndex < LIGHT_MAX);
	LightObject::currentLight++;
}

void LightObject::Update(float deltaTime)
{
}

void LightObject::PostLight(ConstantVariable& constant) const
{
	constant.lightPosition.variable[this->lightIndex] = this->transform.currentTransform * glm::vec4(this->transform.position, 1.0f);
	constant.lightColor.variable[this->lightIndex] = this->lightColor;
	constant.lightStrength.variable[this->lightIndex] = this->lightStrength;
}