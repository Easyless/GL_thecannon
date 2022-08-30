#include "pch.h"
#include "GameObject.h"
#include "framework.h"

GameObject::GameObject(Framework* framework, GLuint shaderProgram, const std::string& meshTag, const std::string& materialTag)
{
	this->framework = framework;
	if (meshTag != "" && shaderProgram != -1)
	{
		this->renderItem = std::make_unique<RenderItem>(shaderProgram, this->framework->meshes[meshTag],&this->framework->materials[materialTag]);
	}
}

RenderItem& GameObject::GetRenderItem()
{
	return *this->renderItem.get();
}

void GameObject::UpdateTransform(glm::mat4 parentTransform)
{
	this->transform.parentTransform = parentTransform;
	auto nowTransform = parentTransform * this->transform.GetMaxtrix();
	this->transform.currentTransform = nowTransform;
	if(this->renderItem != nullptr)
	{
		this->renderItem->worldTrasform.variable = nowTransform;
	}
	if (this->hasSibiling())
	{
		this->GetNextsibiling()->UpdateTransform(parentTransform);
	}
	if (this->hasChild())
	{
		this->GetChild()->UpdateTransform(nowTransform);
	}
}

void GameObject::Update(float deltaTime)
{
	if (this->isActive)
	{

	}
}

void GameObject::KeyHandler(unsigned char key, float x, float y)
{
}

void GameObject::KeyUpHandler(unsigned char key, float x, float y)
{
}

void GameObject::SpecialHandler(int key, float x, float y)
{
}

void GameObject::SpecialUpHandler(int key, float x, float y)
{
}

void GameObject::MouseHandler(int button, int state, float x, float y)
{
}

void GameObject::MotionHandler(float x, float y)
{
}

void GameObject::PassiveMotionHandler(float x, float y)
{
}

void GameObject::Draw()
{
	if (this->renderItem != nullptr && this->isVisible)
	{
		this->renderItem->Draw();
	}
}

void GameObject::Destory()
{
	this->isVisible = false;
	this->isActive = false;
	this->isDestroyed = true;
	this->FunctionChild(
		[](GameObject* obj) -> void
		{
			obj->isVisible = false;
			obj->isActive = false;
			obj->isDestroyed = true;
		}
	);
}

bool GameObject::hasRenderItem() const
{
	return this->renderItem != nullptr;
}
