#pragma once
#include "GL_HEADER.h"
static struct Color
{
	static constexpr glm::vec4 Rgb(int r, int g, int b, float a = 1.0f)
	{
		return glm::vec4(
			((float)r / (float)255),
			((float)g / (float)255),
			((float)b / (float)255),
			a
		);
	}
	static constexpr glm::vec4 Black = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	static constexpr glm::vec4 White = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	static constexpr glm::vec4 Red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	static constexpr glm::vec4 Green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	static constexpr glm::vec4 Blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	static constexpr glm::vec4 Yellow = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	static constexpr glm::vec4 Magenta = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	static constexpr glm::vec4 Cyan = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
};