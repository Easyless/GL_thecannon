#include "pch.h"
#include "GL_HEADER.h"
#include "Utill.h"
#include "framework.h"
#include "VertexArrayObject.h"
#include "LoadObj_Deprecated.h"


#pragma region BuildInlineTwoVertex

VertexArrayObject<2> GetCubeInner()
{
	VertexArrayObject<2> vao;
	vao.Init();
	float vertexPosition[] =
	{
		//1
		1.0, 1.0, 1.0, 1.0,
		-1.0, -1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0, 1.0,
		//
		1.0, -1.0, 1.0, 1.0,
		-1.0, -1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		//2
		1.0,1.0,-1.0,1.0,
		1.0,-1.0,1.0,1.0,
		1.0,1.0,1.0,1.0,
		//
		1.0,-1.0,-1.0,1.0,
		1.0,-1.0,1.0,1.0,
		1.0,1.0,-1.0,1.0,
		//3
		-1.0,-1.0,-1.0,1.0,
		1.0,1.0,-1.0,1.0,
		-1.0,1.0,-1.0,1.0,
		//
		1.0,-1.0,-1.0,1.0,
		1.0,1.0,-1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		//4
		-1.0,1.0,1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		-1.0,1.0,-1.0,1.0,
		//
		-1.0,-1.0,1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		-1.0,1.0,1.0,1.0,
		//5
		1.0,1.0,-1.0,1.0,
		-1.0,1.0,1.0,1.0,
		-1.0,1.0,-1.0,1.0,
		//
		1.0,1.0,1.0,1.0,
		-1.0,1.0,1.0,1.0,
		1.0,1.0,-1.0,1.0,
		//6
		1.0,-1.0,1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		-1.0,-1.0,1.0,1.0,
		//
		1.0,-1.0,-1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		1.0,-1.0,1.0,1.0
	};

	float vertexColor[] =
	{
		//1
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//2
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//3
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//4
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//5
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//6
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1
	};

	vao.Load(0, (void*)vertexPosition, sizeof(float), 4, (arrsize(vertexPosition) / 4));
	vao.Load(1, (void*)vertexColor, sizeof(float), 4, (arrsize(vertexColor) / 4));
	vao.Bind();
	return vao;
}

VertexArrayObject<2> GetCubeOuter()
{
	VertexArrayObject<2> vao;
	vao.Init();
	float vertexPosition[] =
	{
		//1
		-1.0, 1.0, 1.0, 1.0,
		-1.0, -1.0, 1.0, 1.0,
		1.0, 1.0, 1.0, 1.0,
		//
		1.0, 1.0, 1.0, 1.0,
		-1.0, -1.0, 1.0, 1.0,
		1.0, -1.0, 1.0, 1.0,
		//2
		1.0,1.0,1.0,1.0,
		1.0,-1.0,1.0,1.0,
		1.0,1.0,-1.0,1.0,
		//
		1.0,1.0,-1.0,1.0,
		1.0,-1.0,1.0,1.0,
		1.0,-1.0,-1.0,1.0,
		//3
		-1.0,1.0,-1.0,1.0,
		1.0,1.0,-1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		//
		-1.0,-1.0,-1.0,1.0,
		1.0,1.0,-1.0,1.0,
		1.0,-1.0,-1.0,1.0,
		//4
		-1.0,1.0,-1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		-1.0,1.0,1.0,1.0,
		//
		-1.0,1.0,1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		-1.0,-1.0,1.0,1.0,
		//5
		-1.0,1.0,-1.0,1.0,
		-1.0,1.0,1.0,1.0,
		1.0,1.0,-1.0,1.0,
		//
		1.0,1.0,-1.0,1.0,
		-1.0,1.0,1.0,1.0,
		1.0,1.0,1.0,1.0,
		//6
		-1.0,-1.0,1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		1.0,-1.0,1.0,1.0,
		//
		1.0,-1.0,1.0,1.0,
		-1.0,-1.0,-1.0,1.0,
		1.0,-1.0,-1.0,1.0,
	};

	float vertexColor[] =
	{
		//1
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//2
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//3
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//4
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//5
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//6
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1
	};

	vao.Load(0, (void*)vertexPosition, sizeof(float), 4, (arrsize(vertexPosition) / 4));
	vao.Load(1, (void*)vertexColor, sizeof(float), 4, (arrsize(vertexColor) / 4));
	vao.Bind();
	return vao;
}

VertexArrayObject<2> GetPlane()
{
	VertexArrayObject<2> vao;
	vao.Init();
	float vertexPosition[] =
	{
		+1.0, +1.0,0.0,1.0,
		-1.0, +1.0,0.0,1.0,
		-1.0, -1.0,0.0,1.0,
				 
		+1.0, +1.0,0.0,1.0,
		-1.0, -1.0,0.0,1.0,
		+1.0, -1.0,0.0,1.0,
	};

	float vertexColor[] =
	{
		//1
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		//
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
	};

	vao.Load(0, (void*)vertexPosition, sizeof(float), 4, (arrsize(vertexPosition) / 4));
	vao.Load(1, (void*)vertexColor, sizeof(float), 4, (arrsize(vertexColor) / 4));
	vao.Bind();
	return vao;
}


VertexArrayObject<2> GetXYZLine()
{
	VertexArrayObject<2> vao;
	vao.Init();
	float vertexPosition[] =
	{
		//1
		1.0, 0.0, 0.0, 1.0,
		-1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, -1.0, 0.0, 1.0,
		0.0,0.0,1.0,1.0,
		0.0,0.0,-1.0,1.0
	};
	float vertexColor[] =
	{
		1.0, 0.0, 0.0, 1.0,
		1.0, 0.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 1.0, 0.0, 1.0,
		0.0, 0.0, 1.0, 1.0,
		0.0, 0.0, 1.0, 1.0
	};
	vao.Load(0, (void*)vertexPosition, sizeof(float), 4, arrsize(vertexPosition) / 4);
	vao.Load(1, (void*)vertexColor, sizeof(float), 4, arrsize(vertexPosition) / 4);
	vao.Bind();
	return vao;
}

#pragma endregion


VertexArrayObject<3> GetObjVAO(const std::string& dir)
{
	std::vector<glm::vec3> outVertex;
	std::vector<glm::vec3> outNormal;
	loadObj(dir.c_str(), outVertex, outNormal);
	VertexArrayObject<3> result;
	result.Init();
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec4> noramls;
	for (auto v : outVertex)
	{
		vertices.push_back(glm::vec4(v, 1.0f));
		colors.push_back(glm::vec4(1.0f));
	}
	for (auto n : outNormal)
	{
		noramls.push_back(glm::vec4(n, 0.0f));
	}
	result.Load(0, vertices.data(), sizeof(float), 4, vertices.size());
	result.Load(1, colors.data(), sizeof(float), 4, colors.size());
	result.Load(2, noramls.data(), sizeof(float), 4, noramls.size());
	return result;
}

VertexArrayObject<3> GetObjVAOInnerNormal(const std::string& dir)
{
	std::vector<glm::vec3> outVertex;
	std::vector<glm::vec3> outNormal;
	loadObj(dir.c_str(), outVertex, outNormal);
	VertexArrayObject<3> result;
	result.Init();
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec4> noramls;
	for (auto v : outVertex)
	{
		vertices.push_back(glm::vec4(v, 1.0f));
		colors.push_back(glm::vec4(1.0f));
	}
	for (auto n : outNormal)
	{
		noramls.push_back(glm::vec4(-1.0f * n, 0.0f));
	}
	result.Load(0, vertices.data(), sizeof(float), 4, vertices.size());
	result.Load(1, colors.data(), sizeof(float), 4, colors.size());
	result.Load(2, noramls.data(), sizeof(float), 4, noramls.size());
	return result;
}

VertexArrayObject<4> GetObjVAOUV(const std::string& dir)
{
	std::vector<glm::vec3> outVertex;
	std::vector<glm::vec3> outNormal;
	std::vector<glm::vec2> outUv;
	loadObj(dir.c_str(), outVertex, outNormal, outUv);
	VertexArrayObject<4> result;
	result.Init();
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec4> noramls;
	std::vector<glm::vec2> uvs;
	for (auto v : outVertex)
	{
		vertices.push_back(glm::vec4(v, 1.0f));
		colors.push_back(glm::vec4(1.0f));
	}
	for (auto n : outNormal)
	{
		noramls.push_back(glm::vec4(n, 0.0f));
	}
	for (auto n : outUv)
	{
		uvs.push_back(n);
	}
	result.Load(0, vertices.data(), sizeof(float), 4, vertices.size());
	result.Load(1, colors.data(), sizeof(float), 4, colors.size());
	result.Load(2, noramls.data(), sizeof(float), 4, noramls.size());
	result.Load(3, uvs.data(), sizeof(float), 2, uvs.size());
	return result;
}

VertexArrayObject<2> GetUVPlane(const std::string& dir)
{
	std::vector<glm::vec3> outVertex;
	std::vector<glm::vec3> outNormal;
	std::vector<glm::vec2> outUv;
	loadObj(dir.c_str(), outVertex, outNormal, outUv);
	VertexArrayObject<2> result;
	result.Init();
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	for (auto v : outVertex)
	{
		vertices.push_back(glm::vec4(v, 1.0f));
	}
	for (auto n : outUv)
	{
		uvs.push_back(n);
	}
	result.Load(0, vertices.data(), sizeof(float), 4, vertices.size());
	result.Load(1, uvs.data(), sizeof(float), 2, uvs.size());
	return result;
}

void Framework::BuildVertexs()
{
	this->UIPlane = GetUVPlane("Resource/plane.object");
	this->meshes["cube"] = GetObjVAOUV("Resource/cube.object");
	//this->meshes["cubeInner"] = GetObjVAOInnerNormal("Resource/cube.object");
	this->meshes["plane"] = GetObjVAOUV("Resource/plane.object");
	this->meshes["sphere"] = GetObjVAOUV("Resource/sphere.object");
	this->meshes["cylinder"] = GetObjVAOUV("Resource/cylinder.object");
	this->meshes["piramid"] = GetObjVAOUV("Resource/piramid.object");
	this->meshes["cannonbase"] = GetObjVAOUV("Resource/cannonbase.object");
	this->meshes["cannonbarrel"] = GetObjVAOUV("Resource/cannonbarrel.object");
	this->meshes["bomb"] = GetObjVAOUV("Resource/bomb.object");
	this->meshes["target"] = GetObjVAOUV("Resource/target.object");
	this->meshes["targetingpoint"] = GetObjVAOUV("Resource/targetingpoint.object");

	this->meshes["rock"] = GetObjVAOUV("Resource/rock.object");

	this->meshes["building1"] = GetObjVAOUV("Resource/building/tex_building1.object");
	this->meshes["building2"] = GetObjVAOUV("Resource/building/tex_building2.object");
	this->meshes["building3"] = GetObjVAOUV("Resource/building/tex_building3.object");
	this->meshes["building4"] = GetObjVAOUV("Resource/building/tex_building4.object");
	this->meshes["building5"] = GetObjVAOUV("Resource/building/tex_building5.object");
	this->meshes["building6"] = GetObjVAOUV("Resource/building/tex_building6.object");


	/*
	this->meshes["building1"] = GetObjVAOUV("Resource/building/building1.object");
	this->meshes["building2"] = GetObjVAOUV("Resource/building/building2.object");
	this->meshes["building3"] = GetObjVAOUV("Resource/building/building3.object");
	this->meshes["building4"] = GetObjVAOUV("Resource/building/building4.object");
	this->meshes["building5"] = GetObjVAOUV("Resource/building/building5.object");
	this->meshes["building6"] = GetObjVAOUV("Resource/building/building6.object");
	this->meshes["building7"] = GetObjVAOUV("Resource/building/building7.object");
	this->meshes["building8"] = GetObjVAOUV("Resource/building/building8.object");
	this->meshes["building9"] = GetObjVAOUV("Resource/building/building9.object");
	this->meshes["building10"] = GetObjVAOUV("Resource/building/building10.object");
	this->meshes["twinbuilding"] = GetObjVAOUV("Resource/building/TwinBuilding.object");
	*/
	this->meshes["medieval"] = GetObjVAOUV("Resource/building/medieval.object");
	this->meshes["oldhouse"] = GetObjVAOUV("Resource/building/oldhouse.object");
}