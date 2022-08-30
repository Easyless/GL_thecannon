#include "pch.h"
#include "framework.h"
#include "UINumber.h"

UINumber::UINumber(Framework* framework, int count, std::array<std::string, 10> fontDirs, FREE_IMAGE_FORMAT format, glm::vec4 Color, GLuint shaderProgram)
	:UIObject(framework, shaderProgram)
{
	this->textColor = Color;
	this->numberCount = count;
	for (size_t i = 0; i < 10; i++)
	{
		this->fontTexture[i].Create(fontDirs[i], format);
	}

	if (shaderProgram == 0)
	{
		shaderProgram = this->framework->shaderPrograms["ui_def"];
	}
	for (size_t i = 0; i < count; i++)
	{
		this->fontRenderItem.emplace_back(std::make_unique<UIRenderItem>(shaderProgram, this->framework->UIPlane, this->fontTexture[0]));
		this->fontRenderItem[i]->objectColor = this->textColor;
	}
}

void UINumber::Draw()
{
	for (auto& ptr : fontRenderItem)
	{
		ptr->Draw();
	}
}

void UINumber::UpdateTransform(glm::mat4 parentTransform)
{
	float startPos = 0;
	UIObject::UpdateTransform(parentTransform);
	if (this->numberCount % 2)
	{
		//Â¦¼ö
		startPos = (this->spacing / 2) + (this->numberCount / 2) * this->spacing;
	}
	else 
	{
		startPos = (this->numberCount / 2) * this->spacing;
	}
	for (size_t i = 0; i < this->numberCount; i++)
	{
		this->fontRenderItem[i]->worldTrasform =
			this->transform.currentTransform * glm::translate(glm::vec3(startPos - i * this->spacing,0,0));
	}
}

void UINumber::Update(float deltaTime)
{
	int calNum = this->currentValue;
	for (size_t i = 0; i < this->numberCount; i++)
	{
		int num = calNum % 10;
		calNum = calNum / 10;
		this->fontRenderItem[i]->surfaceTexture = this->fontTexture[num];
		this->fontRenderItem[i]->objectColor = this->textColor;
	}
	UIObject::Update(deltaTime);
}
