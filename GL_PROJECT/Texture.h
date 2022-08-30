#pragma once
#include <string>
#include <FreeImage.h>
#include "GL_HEADER.h"


struct Texture
{
	~Texture();
	GLuint id = 0;
	void Create(const std::string& dir, FREE_IMAGE_FORMAT format, bool repeat = true);
	void CreateCubeMap(const std::array<std::string,6> dirs, FREE_IMAGE_FORMAT format, bool repeat = true);
	void Bind(size_t index) const;
};