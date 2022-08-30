#pragma once
#include "GL_HEADER.h"
#include <vector>
int loadObj(const char* filename, std::vector< glm::vec3 >& _outvertex, std::vector< glm::vec3 >& _outnormal);
int loadObj(const char* filename, std::vector< glm::vec3 >& _outvertex, std::vector< glm::vec3 >& _outnormal, std::vector< glm::vec2 >& _outuv);