#include "pch.h"
#include "GL_HEADER.h"
#include "framework.h"
#include "Collision.h"
#include "framework.h"
#include "RenderItem.h"
#include "Color.h"
#include "Utill.h"

CollisionBox::CollisionBox(Framework* framework, const std::string& tag)
	: GameObject(framework, framework->shaderPrograms["default"], "cube", "lightProbe"), phyTag(tag)
{
	this->renderItem->drawType = GL_TRIANGLES;
	this->renderItem->isLocalWireFramed = true;
	this->renderItem->objectColor = Color::Green;
}

void CollisionBox::UpdateTransform(glm::mat4 parentTransform)
{
	GameObject::UpdateTransform(parentTransform);
	this->transform.currentTransform =
		this->transform.currentTransform *
		glm::inverse(glm::mat4(glm::mat3(this->transform.currentTransform))) *
		glm::scale(this->transform.scale);
	this->renderItem->worldTrasform = this->transform.currentTransform;
}

void CollisionBox::PostOnCollisionFunc(CollisionFunc func)
{
	this->OnCollision = func;
}

void CollisionBox::HandleCollision(CollisionBox& other)
{
	if ((this->OnCollision != nullptr || other.OnCollision != nullptr) && this->isActive)
	{
		if (this->CheckCollision(other))
		{
			if (this->OnCollision != nullptr)
			{
				this->OnCollision(this, &other,
					glm::mix(
						this->transform.currentTransform * glm::vec4(glm::vec3(0.0f), 1.0f),
						other.transform.currentTransform * glm::vec4(glm::vec3(0.0f), 1.0f),
						0.5f
					)
				);
			}
			if (other.OnCollision != nullptr)
			{
				other.OnCollision(&other,
					this,
					glm::mix(
						this->transform.currentTransform * glm::vec4(glm::vec3(0.0f), 1.0f),
						other.transform.currentTransform * glm::vec4(glm::vec3(0.0f), 1.0f),
						0.5f
					)
				);
			}
		}
	}
}


auto CollisionBox::GetCurrentBoundBox() const
{
	glm::vec4 pointMax = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 pointMin = glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	pointMax = this->transform.currentTransform * pointMax;
	pointMin = this->transform.currentTransform * pointMin;

	if (pointMax.x < pointMin.x)
	{
		swap_item(pointMax.x, pointMin.x);
	}
	if (pointMax.y < pointMin.y)
	{
		swap_item(pointMax.y, pointMin.y);
	}
	if (pointMax.z < pointMin.z)
	{
		swap_item(pointMax.z, pointMin.z);
	}

	return std::make_pair(pointMax, pointMin);
}

bool CollisionBox::CheckCollision(const CollisionBox& other) const
{
	auto a = this->GetCurrentBoundBox();
	auto b = other.GetCurrentBoundBox();
	//fprintf(stdout, "col 1 max: %f, %f, %f\n",a.first.x, a.first.y, a.first.z);
	//fprintf(stdout, "col 1 min: %f, %f, %f\n",a.second.x, a.second.y, a.second.z);
	//fprintf(stdout, "col 2 max: %f, %f, %f\n", b.first.x, b.first.y, b.first.z);
	//fprintf(stdout, "col 2 min: %f, %f, %f\n", b.second.x, b.second.y, b.second.z);
	return CollisionBox::AABB(a.first, a.second, b.first, b.second);
}

bool CollisionBox::AABB(glm::vec3 a_max, glm::vec3 a_min, glm::vec3 b_max, glm::vec3 b_min)
{
	if (a_max.x < b_min.x || a_min.x > b_max.x)
	{
		return false;
	}
	else if (a_max.y < b_min.y || a_min.y > b_max.y)
	{
		return false;
	}
	else if (a_max.z < b_min.z || a_min.z > b_max.z)
	{
		return false;
	}
	else
	{
		return true;
	}
}
