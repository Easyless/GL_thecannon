#include "pch.h"
#include "framework.h"
#include "Texture.h"

void Framework::BuildTexture()
{
	{
		Texture tex;
		tex.Create("Resource/texture/white.bmp", FIF_BMP);
		this->textures["default"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/bricks3.dds", FIF_DDS);
		this->textures["bricks3"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/tree0.bmp", FIF_BMP, false);
		this->textures["tree0"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/tree1.bmp", FIF_BMP, false);
		this->textures["tree1"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/tree2.bmp", FIF_BMP, false);
		this->textures["tree2"] = tex;
	}
	

	// °Ç¹°
	{
		Texture tex;
		tex.Create("Resource/texture/building_tex/tex_building1_diff.png", FIF_PNG, false);
		this->textures["building1_diff"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/building_tex/tex_building2_diff.png", FIF_PNG, false);
		this->textures["building2_diff"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/building_tex/tex_building3_diff.png", FIF_PNG, false);
		this->textures["building3_diff"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/building_tex/tex_building4_diff.png", FIF_PNG, false);
		this->textures["building4_diff"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/building_tex/tex_building5_diff.png", FIF_PNG, false);
		this->textures["building5_diff"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/building_tex/tex_building6_diff.png", FIF_PNG, false);
		this->textures["building6_diff"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/exp/6.png", FIF_PNG, true);
		this->textures["exp"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/rock.png", FIF_PNG, true);
		this->textures["rock"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/rockrockNormalmap.tiff", FIF_TIFF, true);
		this->textures["rock_norm"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/tex_withnormal/gravel/gravel_01_diffuse.jpg", FIF_JPEG, true);
		this->textures["gravel"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/tex_withnormal/gravel/gravel_01_normal.jpg", FIF_JPEG, true);
		this->textures["gravel_norm"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/tex_withnormal/dirt/dirt_01_diffuse.jpg", FIF_JPEG, true);
		this->textures["sand"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/tex_withnormal/dirt/dirt_01_normal.jpg", FIF_JPEG, true);
		this->textures["sand_norm"] = tex;
	}
	{
		Texture tex;
		tex.Create("Resource/texture/target_maker.png", FIF_PNG, true);
		this->textures["marker"] = tex;
	}

	{
		Texture tex;
		tex.Create("Resource/ui/rotate_marker.png", FIF_PNG, true);
		this->textures["rotator"] = tex;
	}

	{
		Texture tex;
		tex.CreateCubeMap(
			{
				"Resource/texture/skymap_second/right.jpg" ,
				"Resource/texture/skymap_second/left.jpg" ,
				"Resource/texture/skymap_second/top.jpg" ,
				"Resource/texture/skymap_second/bottom.jpg" ,
				"Resource/texture/skymap_second/front.jpg" ,
				"Resource/texture/skymap_second/back.jpg" ,
			},
			FIF_JPEG,
			false);
		this->textures["skybox"] = tex;
	}
}

void Framework::SetDefaultTexture()
{
	for (auto& m : this->materials)
	{
		for (auto& i : m.second.textures)
		{
			if (i.id == 0)
			{
				i = this->textures["default"];
			}
		}
	}
}
