#pragma once
#include "GL_HEADER.h"
#include <tuple>
#include <iostream>
#include <fstream>
#include <algorithm>

void GlPosToWinPos(int size_x, int size_y, int& x, int& y);
void WinPosToGlPos(int size_x, int size_y, int& x, int& y);

std::pair<int, int> GlPosToWinPosPair(int size_x, int size_y, int x, int y);
std::pair<int, int> WinPosToGlPosPair(int size_x, int size_y, int x, int y);


constexpr size_t ERROR_LOG_SIZE = 512;

GLuint CreateShaderProgram(const char* vsDir, const char* psDir);
GLuint LoadShaderObject(const char* dir, GLenum shaderType);
GLuint ComplieShaderObject(const GLchar* data, GLenum shaderType);


template<typename T, size_t N>
size_t arrsize(T(&)[N]) { return N; }

template<typename Ty>
Ty soy_min(const Ty& a, const Ty& b)
{
	return (a < b) ? (a) : (b);
}

template<typename Ty>
Ty soy_max(const Ty& a, const Ty& b)
{
	return (a > b) ? (a) : (b);
}

template<typename Ty>
Ty soy_clamp(const Ty& target, const Ty& min, const Ty& max)
{
	return soy_max(soy_min(target, max), min);
}

template <typename Ty, size_t size>
std::array<Ty, size> FilledArray(Ty value)
{
	std::array<Ty, size> arr;
	std::fill(arr.begin(), arr.end(), value);
	return arr;
}

template<typename Ty>
void swap_item(Ty& a, Ty& b)
{
	Ty temp = a;
	a = b;
	b = temp;
}
