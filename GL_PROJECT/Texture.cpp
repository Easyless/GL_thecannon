#include "pch.h"
#include "Texture.h"

void Texture::Create(const std::string& dir, FREE_IMAGE_FORMAT format, bool repeat)
{
	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);
	if (repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	FIBITMAP* img = FreeImage_Load(format, dir.c_str(), 0);
	FIBITMAP* pImage = FreeImage_ConvertTo32Bits(img);
	
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
		0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));

	FreeImage_Unload(pImage);
	FreeImage_Unload(img);
}

void Texture::CreateCubeMap(const std::array<std::string, 6> dirs, FREE_IMAGE_FORMAT format, bool repeat)
{
	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->id);
	if (false)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (size_t i = 0; i < dirs.size(); i++)
	{
		FIBITMAP* img = FreeImage_Load(format, dirs[i].c_str(), 0);
		bool a = FreeImage_FlipVertical(img);
		FIBITMAP* pImage = FreeImage_ConvertTo32Bits(img);
		if (img == nullptr)
		{
			std::cout << "Can't load Texture Image" << std::endl;
		}
		int nWidth = FreeImage_GetWidth(pImage);
		int nHeight = FreeImage_GetHeight(pImage);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, nWidth, nHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));


		FreeImage_Unload(pImage);
		FreeImage_Unload(img);
	}
}


void Texture::Bind(size_t index) const
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, this->id);
}

Texture::~Texture()
{
	if (this->id != 0)
	{
		glDeleteTextures(0, &this->id);
	}
}
