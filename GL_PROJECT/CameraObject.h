#pragma once
#include <functional>
#include "GameObject.h"
#include "LambdaGameObject.h"
class CameraObject : public GameObject
{
public:
	bool isPerspective = true;
	float perspFovY = 45.0f;

	float orthoLeft = -1.0f;
	float orthoRight = 1.0f;
	float orthoBottom = -1.0f;
	float orthoTop = 1.0f;

	float nearZ = 0.01f;
	float farZ = 1000.0f;
public:
	CameraObject(Framework* framework, GLuint shaderProgram = -1, const std::string& meshTag = "", const std::string& materialTag = "default");
	void Update(float deltaTime) override;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix() const;
};
