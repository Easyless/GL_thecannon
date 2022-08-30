#pragma once
#include "GL_HEADER.h"

template <size_t vbo_count>
struct VertexArrayObject
{
	using ThisType = VertexArrayObject<vbo_count>;
	GLuint vao = 0;
	std::array<GLuint, vbo_count> vbos;
	size_t vertex_count = 0;
	VertexArrayObject()
		:vbos{}
	{

	}
	void Init()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(vbo_count, vbos.data());
	}
	void Destory()
	{
		for (auto i : vbos)
		{
			glDeleteBuffers(1, &i);
		}
		glDeleteVertexArrays(1, &this->vao);
	}

	void Load(size_t index, void* buffer, size_t element_size, size_t element_count, size_t vertex_count, GLenum type = GL_FLOAT, GLenum usage = GL_STATIC_DRAW)
	{
		this->Bind();
		this->vertex_count = vertex_count;
		glBindBuffer(GL_ARRAY_BUFFER, vbos[index]);
		glBufferData(GL_ARRAY_BUFFER, element_size * element_count * vertex_count, buffer, GL_STATIC_DRAW);
		glVertexAttribPointer(index, element_count, type, false, 0, 0);
		glEnableVertexAttribArray(index);
	}
	void Bind() const
	{
		glBindVertexArray(vao);
	}
};