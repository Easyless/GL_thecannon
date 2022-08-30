#include "pch.h"
#include "UIObject.h"
#include "framework.h"

UIObject::UIObject(Framework* framework, GLuint shaderProgram)
	:framework(framework)
{
	this->isVisible = true;
	if (shaderProgram == 0)
	{
		shaderProgram = this->framework->shaderPrograms["ui_def"];
	}
	this->renderItem = std::make_unique<UIRenderItem>(shaderProgram, this->framework->UIPlane, this->framework->textures["default"]);
}

UIObject::UIObject(Framework* framework, const std::string& dir, FREE_IMAGE_FORMAT format, GLuint shaderProgram)
	:framework(framework)
{
	this->isVisible = true;
	if (shaderProgram == 0)
	{
		shaderProgram = this->framework->shaderPrograms["ui_def"];
	}
	this->renderItem = std::make_unique<UIRenderItem>(shaderProgram, this->framework->UIPlane, dir, format);
}

UIRenderItem& UIObject::GetRenderItem()
{
	return *this->renderItem;
}

void UIObject::Draw()
{
	if (this->isVisible && this->renderItem != nullptr)
	{
		this->renderItem->Draw();
	}
}

void UIObject::Update(float deltaTime)
{
	this->OnUpdate.Execute(deltaTime, this);
}

void UIObject::KeyHandler(unsigned char key, float x, float y)
{
	if (this->CheckClicked(x,y))
	{
		this->OnKeyDown.Execute(key, x, y, this);
	}
}

void UIObject::KeyUpHandler(unsigned char key, float x, float y)
{
	this->OnKeyUp.Execute(key, x, y, this);
}

void UIObject::SpecialHandler(int key, float x, float y)
{
	this->OnSpecial.Execute(key, x, y, this);
}

void UIObject::SpecialUpHandler(int key, float x, float y)
{
	this->OnSpecialUp.Execute(key, x, y, this);
}

void UIObject::MouseHandler(int button, int state, float x, float y)
{
	if (this->CheckClicked(x, y))
	{
		this->OnClick.Execute(button, state, x, y, this);
	}
}

void UIObject::MotionHandler(float x, float y)
{
	this->OnMotion.Execute(x, y, this);
}

void UIObject::PassiveMotionHandler(float x, float y)
{
	this->OnPassiveMotion.Execute(x, y, this);
}

bool UIObject::CheckClicked(float x, float y) const
{
	auto result = glm::inverse(
		this->framework->uiConstant.projTransform.variable * this->framework->uiConstant.viewTransform.variable * this->transform.currentTransform
	) * glm::vec4(x,y,y,1);

	return glm::abs(result.x / result.w) <= 1.0f && glm::abs(result.z / result.w) <= 1.0f;
}

void UIObject::UpdateTransform(glm::mat4 parentTransform)
{
	this->transform.parentTransform = parentTransform;
	auto nowTransform = parentTransform * this->transform.GetMaxtrix();
	this->transform.currentTransform = nowTransform;
	if (this->renderItem != nullptr)
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
