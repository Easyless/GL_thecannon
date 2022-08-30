#include "pch.h"
#include "CameraObject.h"
#include "framework.h"

CameraObject::CameraObject(Framework* framework, GLuint shaderProgram, const std::string& meshTag, const std::string& materialTag)
	: GameObject(framework, shaderProgram, meshTag, materialTag)
{
	this->orthoLeft *= this->framework->aspect;
	this->orthoRight *= this->framework->aspect;
}

void CameraObject::Update(float deltaTime)
{
}

glm::mat4 CameraObject::GetViewMatrix() const
{
	auto eye4 = this->transform.currentTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	auto at4 = this->transform.currentTransform * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);
	auto up4 = this->transform.currentTransform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec3 eye = glm::vec3(eye4.x, eye4.y, eye4.z) / eye4.w;
	glm::vec3 at = glm::vec3(at4.x, at4.y, at4.z) / at4.w;
	glm::vec3 up = glm::vec3(up4.x, up4.y, up4.z) / up4.w;
	return
		 glm::lookAt(
			eye,
			at,
			up - eye
		);
}

glm::mat4 CameraObject::GetProjMatrix() const
{
	if (this->isPerspective)
	{
		return glm::perspective(glm::radians(this->perspFovY), this->framework->aspect, this->nearZ, this->farZ);
	}
	else
	{
		return glm::ortho(this->orthoLeft,this->orthoRight,this->orthoBottom,this->orthoTop, this->nearZ, this->farZ);
	}
}
