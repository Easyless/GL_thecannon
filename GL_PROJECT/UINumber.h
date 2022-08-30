#pragma once
#include "UIObject.h"
#include "Color.h"

class UINumber : public UIObject
{
public:
	UINumber(Framework* framework, int count, std::array<std::string,10> fontDirs, FREE_IMAGE_FORMAT format = FIF_PNG, glm::vec4 Color = Color::Black, GLuint shaderProgram = 0);
	int numberCount = 0;
	int currentValue = 0;
	float spacing = 1.5f;
	glm::vec4 textColor = Color::Black;
	std::array<Texture, 10> fontTexture;
	std::vector<std::unique_ptr<UIRenderItem>> fontRenderItem;
	void Draw() override;
	void UpdateTransform(glm::mat4 parentTransform) override;
	void Update(float deltaTime) override;
};