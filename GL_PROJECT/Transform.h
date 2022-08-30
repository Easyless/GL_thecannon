#pragma once
#include "GL_HEADER.h"
struct Transform
{
	static constexpr glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	static constexpr glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	static constexpr glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);


	glm::vec3 lastScale = glm::vec3(1.0f);
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 rotation = glm::vec3(0.0f);
	glm::vec3 scale = glm::vec3(1.0f);
	glm::vec3 pivot_move = glm::vec3(0.0f);

	glm::mat4 localRotate = glm::mat4(1.0f);

	glm::mat4 worldTransform = glm::mat4(1.0f);

	glm::mat4 currentTransform = glm::mat4(1.0f);
	glm::mat4 parentTransform = glm::mat4(1.0f);

	glm::vec3 Forward() const
	{
		glm::vec4 temp(0.0f, 0.0f, 1.0f,1.0f);
		temp = localRotate
			* glm::rotate(glm::radians(rotation.x), xAxis)
			* glm::rotate(glm::radians(rotation.y), yAxis)
			* glm::rotate(glm::radians(rotation.z), zAxis)
			* temp;
		return glm::normalize(glm::vec3(temp.x, temp.y, temp.z) / temp.w);
	}
	glm::vec3 BackWard() const
	{
		glm::vec4 temp(0.0f, 0.0f, -1.0f, 1.0f);
		temp = localRotate
			* glm::rotate(glm::radians(rotation.x), xAxis)
			* glm::rotate(glm::radians(rotation.y), yAxis)
			* glm::rotate(glm::radians(rotation.z), zAxis)
			* temp;
		return glm::normalize(glm::vec3(temp.x, temp.y, temp.z) / temp.w);
	}
	glm::vec3 Left() const
	{
		glm::vec4 temp(1.0f, 0.0f, 0.0f, 1.0f);
		temp = localRotate
			* glm::rotate(glm::radians(rotation.x), xAxis)
			* glm::rotate(glm::radians(rotation.y), yAxis)
			* glm::rotate(glm::radians(rotation.z), zAxis)
			* temp;
		return glm::normalize(glm::vec3(temp.x, temp.y, temp.z) / temp.w);
	}
	glm::vec3 Right() const
	{
		glm::vec4 temp(-1.0f, 0.0f, 0.0f, 1.0f);
		temp = localRotate
			* glm::rotate(glm::radians(rotation.x), xAxis)
			* glm::rotate(glm::radians(rotation.y), yAxis)
			* glm::rotate(glm::radians(rotation.z), zAxis)
			* temp;
		return glm::normalize(glm::vec3(temp.x, temp.y, temp.z) / temp.w);
	}
	glm::vec3 Up() const
	{
		glm::vec4 temp(0.0f, 1.0f, 0.0f, 1.0f);
		temp = localRotate
			* glm::rotate(glm::radians(rotation.x), xAxis)
			* glm::rotate(glm::radians(rotation.y), yAxis)
			* glm::rotate(glm::radians(rotation.z), zAxis)
			* temp;
		return glm::normalize(glm::vec3(temp.x, temp.y, temp.z) / temp.w);
	}
	glm::vec3 Down() const
	{
		glm::vec4 temp(0.0f, -1.0f, 0.0f, 1.0f);
		temp = localRotate
			* glm::rotate(glm::radians(rotation.x), xAxis)
			* glm::rotate(glm::radians(rotation.y), yAxis)
			* glm::rotate(glm::radians(rotation.z), zAxis)
			* temp;
		return glm::normalize(glm::vec3(temp.x, temp.y, temp.z) / temp.w);
	}

	void Rotate(glm::mat4 rotateMat)
	{
		this->localRotate = rotateMat * this->localRotate;
	}
	glm::mat4 GetMaxtrix() const
	{
		return glm::translate(this->position)
			* glm::scale(this->lastScale)
			* localRotate
			* glm::rotate(glm::radians(rotation.x), xAxis)
			* glm::rotate(glm::radians(rotation.y), yAxis)
			* glm::rotate(glm::radians(rotation.z), zAxis)
			* glm::scale(this->scale)
			* glm::translate(this->pivot_move)
			* this->worldTransform;
	}
};