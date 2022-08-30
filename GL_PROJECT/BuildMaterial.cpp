#include "pch.h"
#include "framework.h"
#include "Material.h"
#include "Color.h"

void Framework::BuildMaterials()
{
	{
		Material mat;
		this->materials["default"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		this->materials["planet"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::Red;
		mat.shininess = 128;
		this->materials["red"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = glm::vec4(1.0, 0.0, 0.0, 0.2);
		mat.shininess = 128;
		this->materials["alphared"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::Green;
		mat.shininess = 128;
		this->materials["green"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::Blue;
		mat.shininess = 128;
		this->materials["blue"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.emissive = Color::White;
		mat.lightAffect = 0.0;
		this->materials["lightProbe"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 1;
		mat.emissive = Color::White;
		mat.lightAffect = 0.0;
		this->materials["offProbe"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.emissive = Color::White;
		mat.lightAffect = 0.0;
		this->materials["bounding"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.AddTexture(0, this->textures["bricks3"]);
		this->materials["bricks"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.AddTexture(0, this->textures["rock"]);
		mat.AddTexture(1, this->textures["rock_norm"]);
		this->materials["rock"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 32;
		mat.AddTexture(0, this->textures["sand"]);
		mat.AddTexture(1, this->textures["sand_norm"]);
		this->materials["sand"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.AddTexture(0, this->textures["gravel"]);
		mat.AddTexture(1, this->textures["gravel_norm"]);
		this->materials["gravel"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.AddTexture(0, this->textures["tree0"]);
		this->materials["tree0"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.AddTexture(0, this->textures["tree1"]);
		this->materials["tree1"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.AddTexture(0, this->textures["tree2"]);
		this->materials["tree2"] = mat;
	}
	{
		Material mat;
		mat.lightAffect = 0.0;
		mat.AddTexture(0, this->textures["skybox"]);
		this->materials["skybox"] = mat;
	}


	// �ǹ�
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 200;
		mat.AddTexture(0, this->textures["building1_diff"]);
		this->materials["building1_diff"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 200;
		mat.AddTexture(0, this->textures["building2_diff"]);
		this->materials["building2_diff"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 200;
		mat.AddTexture(0, this->textures["building3_diff"]);
		this->materials["building3_diff"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 200;
		mat.AddTexture(0, this->textures["building4_diff"]);
		this->materials["building4_diff"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 200;
		mat.AddTexture(0, this->textures["building5_diff"]);
		this->materials["building5_diff"] = mat;
	}
	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 200;
		mat.AddTexture(0, this->textures["building6_diff"]);
		this->materials["building6_diff"] = mat;
	}

	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.lightAffect = 0.0f;
		mat.emissive = Color::White;
		mat.lightAffect = 0.0;
		mat.AddTexture(0, this->textures["exp"]);
		this->materials["exp"] = mat;
	}

	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.lightAffect = 0.0f;
		mat.emissive = Color::White;
		mat.lightAffect = 0.0;
		mat.AddTexture(0, this->textures["marker"]);
		this->materials["marker"] = mat;
	}

	{
		Material mat;
		mat.diffuseAlbedo = Color::White;
		mat.shininess = 128;
		mat.lightAffect = 0.0f;
		mat.emissive = Color::White;
		mat.lightAffect = 0.0;
		mat.AddTexture(0, this->textures["rotator"]);
		this->materials["rotator"] = mat;
	}
}