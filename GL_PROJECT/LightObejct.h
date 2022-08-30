#pragma once
#include <functional>
#include "GameObject.h"
#include "MacroDefined.h"

struct ConstantVariable;

class LightObject : public GameObject
{
public:
	float lightStrength = 1.0f;
	glm::vec4 lightColor = glm::vec4(1.0f);
	size_t lightIndex = 0;
protected:
	static size_t currentLight;
	static const size_t maxLight = LIGHT_MAX;
public:
	LightObject(Framework* framework, GLuint shaderProgram = -1, const std::string& meshTag = "", const std::string& materialTag = "default");
	void Update(float deltaTime) override;
	void PostLight(ConstantVariable& constant) const;
};
