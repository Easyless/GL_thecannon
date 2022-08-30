#pragma once
#include <list>
#include <string>

#include "GL_HEADER.h"

class VertexObjectManager
{
private:
	std::list<GLuint> vaoMem;
	std::list<GLuint> vboMem;
	std::map<std::string, GLuint> tagMap;
public:
	GLuint RequestVAO(const std::string& tag = "");
	GLuint RequestVBO();
	GLuint GetVAO(const std::string& tag) const;
	void PostVAO(const std::string& tag, );
	~VertexObjectManager();
};