#include "pch.h"
#include "framework.h"
#include "GameObject.h"
#include "LambdaGameObject.h"
#include "CameraObject.h"
#include "LambdaCameraObject.h"
#include "MouseCameraObject.h"
#include "Utill.h"
#include "Color.h"
#include <random>

void Framework::BuildMapObjects()
{
	auto terrain = new LambdaGameObject(this, this->shaderPrograms["terrain"], "plane", "sand");
	terrain->GetRenderItem().drawType = GL_TRIANGLES;
	terrain->GetRenderItem().objectColor = Color::Rgb(207, 187, 126);
	terrain->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 130.0f;
	terrain->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 30.0f);

	this->opaqueObjects.emplace_back(terrain);
	this->objects.emplace_back(terrain);
	this->parent->AddChild(terrain);

	auto terrain_1 = new LambdaGameObject(this, this->shaderPrograms["terrain"], "plane", "gravel");
	terrain_1->GetRenderItem().drawType = GL_TRIANGLES;
	terrain_1->isVisible = false;
	terrain_1->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 130.0f;
	terrain_1->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 30.0f);
	terrain_1->PostKeyFunction(
		[terrain](unsigned char key, int x, int y, LambdaGameObject* self)
		{
			static bool onTHIS = false;
			if (key == '3')
			{
				onTHIS = !onTHIS;
				if (onTHIS)
				{
					self->isVisible = true;
					terrain->isVisible = false;
				}
				else
				{
					self->isVisible = false;
					terrain->isVisible = true;
				}
			}
		});
	this->opaqueObjects.emplace_back(terrain_1);
	this->objects.emplace_back(terrain_1);
	this->parent->AddChild(terrain_1);

	auto rock = new GameObject(this, this->shaderPrograms["terrain"], "rock", "rock");
	rock->GetRenderItem().drawType = GL_TRIANGLES;
	rock->GetRenderItem().objectColor = Color::White;
	rock->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 3.0f;
	rock->transform.position.y = -2.0f;
	//terrain->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(rock);
	this->objects.emplace_back(rock);
	this->parent->AddChild(rock);

	auto Building_1 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_1->GetRenderItem().drawType = GL_TRIANGLES;
	Building_1->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_1->transform.position.x = 10.0f;
	Building_1->transform.position.z = 10.0f;
	Building_1->GetRenderItem().isLocalTwoSide = true;
	Building_1->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_1);
	this->objects.emplace_back(Building_1);
	this->parent->AddChild(Building_1);

	auto collision_1 = new CollisionBox(this, "building");
	collision_1->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_1->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_1);
	this->objects.emplace_back(collision_1);
	Building_1->AddChild(collision_1);

	auto Building_2 = new GameObject(this, currentShaderProgram, "building2", "building2_diff");
	Building_2->GetRenderItem().drawType = GL_TRIANGLES;
	Building_2->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_2->transform.position.x = 30.0f;
	Building_2->transform.position.z = 0.0f;
	Building_2->GetRenderItem().isLocalTwoSide = true;
	Building_2->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_2);
	this->objects.emplace_back(Building_2);
	this->parent->AddChild(Building_2);

	auto collision_2 = new CollisionBox(this, "building");
	collision_2->transform.position = glm::vec3(0.0f, 2.75f, 0.0f);
	collision_2->transform.scale = glm::vec3(5.8f, 3.1f, 3.8f);
	this->collisionObjects.emplace_back(collision_2);
	this->objects.emplace_back(collision_2);
	Building_2->AddChild(collision_2);


	auto Building_3 = new GameObject(this, currentShaderProgram, "building3", "building3_diff");
	Building_3->GetRenderItem().drawType = GL_TRIANGLES;
	Building_3->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_3->transform.position.x = 15.0f;
	Building_3->transform.position.z = -15.0f;
	Building_3->GetRenderItem().isLocalTwoSide = true;
	Building_3->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_3);
	this->objects.emplace_back(Building_3);
	this->parent->AddChild(Building_3);

	auto collision_3 = new CollisionBox(this, "building");
	collision_3->transform.position = glm::vec3(+0.5f, 3.0f, 0.7f);
	collision_3->transform.scale = glm::vec3(3.0f, 3.5f, 4.35f);
	this->collisionObjects.emplace_back(collision_3);
	this->objects.emplace_back(collision_3);
	Building_3->AddChild(collision_3);

	auto Building_5 = new GameObject(this, currentShaderProgram, "building5", "building5_diff");
	Building_5->GetRenderItem().drawType = GL_TRIANGLES;
	Building_5->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_5->transform.position.x = -30.0f;
	Building_5->transform.position.z = 0.0f;
	Building_5->GetRenderItem().isLocalTwoSide = true;
	Building_5->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_5);
	this->objects.emplace_back(Building_5);
	this->parent->AddChild(Building_5);

	auto collision_5 = new CollisionBox(this, "building");
	collision_5->transform.position = glm::vec3(-0.2f, 4.5f, 0.2f);
	collision_5->transform.scale = glm::vec3(4.5f, 4.8f, 4.35f);
	this->collisionObjects.emplace_back(collision_5);
	this->objects.emplace_back(collision_5);
	Building_5->AddChild(collision_5);

	auto Building_6 = new GameObject(this, currentShaderProgram, "building6", "building6_diff");
	Building_6->GetRenderItem().drawType = GL_TRIANGLES;
	Building_6->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_6->transform.position.x = 0.0f;
	Building_6->transform.position.z = -30.0f;
	Building_6->GetRenderItem().isLocalTwoSide = true;
	Building_6->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_6);
	this->objects.emplace_back(Building_6);
	this->parent->AddChild(Building_6);

	auto collision_6 = new CollisionBox(this, "building");
	collision_6->transform.position = glm::vec3(0.0f, 8.2f, 0.4f);
	collision_6->transform.scale = glm::vec3(7.8f, 8.5f, 6.45f);
	this->collisionObjects.emplace_back(collision_6);
	this->objects.emplace_back(collision_6);
	Building_6->AddChild(collision_6);

	auto Building_7 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_7->GetRenderItem().drawType = GL_TRIANGLES;
	Building_7->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_7->transform.position.x = 30.0f;
	Building_7->transform.position.z = -27.0f;
	Building_7->GetRenderItem().isLocalTwoSide = true;
	Building_7->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_7);
	this->objects.emplace_back(Building_7);
	this->parent->AddChild(Building_7);

	auto collision_7 = new CollisionBox(this, "building");
	collision_7->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_7->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_7);
	this->objects.emplace_back(collision_7);
	Building_7->AddChild(collision_7);

	auto Building_8 = new GameObject(this, currentShaderProgram, "building4", "building4_diff");
	Building_8->GetRenderItem().drawType = GL_TRIANGLES;
	Building_8->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_8->transform.position.x = 45.0f;
	Building_8->transform.position.z = -40.0f;
	Building_8->GetRenderItem().isLocalTwoSide = true;
	Building_8->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_8);
	this->objects.emplace_back(Building_8);
	this->parent->AddChild(Building_8);

	auto collision_8 = new CollisionBox(this, "building");
	collision_8->transform.position = glm::vec3(-0.2f, 3.2f, 0.1f);
	collision_8->transform.scale = glm::vec3(4.7f, 3.8f, 4.2f);
	this->collisionObjects.emplace_back(collision_8);
	this->objects.emplace_back(collision_8);
	Building_8->AddChild(collision_8);

	auto Building_9 = new GameObject(this, currentShaderProgram, "building3", "building3_diff");
	Building_9->GetRenderItem().drawType = GL_TRIANGLES;
	Building_9->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_9->transform.position.x = 55.0f;
	Building_9->transform.position.z = -30.0f;
	Building_9->GetRenderItem().isLocalTwoSide = true;
	Building_9->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_9);
	this->objects.emplace_back(Building_9);
	this->parent->AddChild(Building_9);

	auto collision_9 = new CollisionBox(this, "building");
	collision_9->transform.position = glm::vec3(+0.5f, 3.0f, 0.7f);
	collision_9->transform.scale = glm::vec3(3.0f, 3.5f, 4.35f);
	this->collisionObjects.emplace_back(collision_9);
	this->objects.emplace_back(collision_9);
	Building_9->AddChild(collision_9);

	auto Building_10 = new GameObject(this, currentShaderProgram, "building4", "building4_diff");
	Building_10->GetRenderItem().drawType = GL_TRIANGLES;
	Building_10->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_10->transform.position.x = 65.0f;
	Building_10->transform.position.z = -20.0f;
	Building_10->GetRenderItem().isLocalTwoSide = true;
	Building_10->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_10);
	this->objects.emplace_back(Building_10);
	this->parent->AddChild(Building_10);

	auto collision_10 = new CollisionBox(this, "building");
	collision_10->transform.position = glm::vec3(-0.2f, 3.2f, 0.1f);
	collision_10->transform.scale = glm::vec3(4.7f, 3.8f, 4.2f);
	this->collisionObjects.emplace_back(collision_10);
	this->objects.emplace_back(collision_10);
	Building_10->AddChild(collision_10);

	auto Building_11 = new GameObject(this, currentShaderProgram, "building5", "building5_diff");
	Building_11->GetRenderItem().drawType = GL_TRIANGLES;
	Building_11->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_11->transform.position.x = 25.0f;
	Building_11->transform.position.z = -15.0f;
	Building_11->GetRenderItem().isLocalTwoSide = true;
	Building_11->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_11);
	this->objects.emplace_back(Building_11);
	this->parent->AddChild(Building_11);

	auto collision_11 = new CollisionBox(this, "building");
	collision_11->transform.position = glm::vec3(-0.2f, 4.5f, 0.2f);
	collision_11->transform.scale = glm::vec3(4.5f, 4.8f, 4.35f);
	this->collisionObjects.emplace_back(collision_11);
	this->objects.emplace_back(collision_11);
	Building_11->AddChild(collision_11);

	auto Building_12 = new GameObject(this, currentShaderProgram, "building6", "building6_diff");
	Building_12->GetRenderItem().drawType = GL_TRIANGLES;
	Building_12->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_12->transform.position.x = 45.0f;
	Building_12->transform.position.z = -12.0f;
	Building_12->GetRenderItem().isLocalTwoSide = true;
	Building_12->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_12);
	this->objects.emplace_back(Building_12);
	this->parent->AddChild(Building_12);

	auto collision_12 = new CollisionBox(this, "building");
	collision_12->transform.position = glm::vec3(0.0f, 8.2f, 0.4f);
	collision_12->transform.scale = glm::vec3(7.8f, 8.5f, 6.45f);
	this->collisionObjects.emplace_back(collision_12);
	this->objects.emplace_back(collision_12);
	Building_12->AddChild(collision_12);

	auto Building_13 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_13->GetRenderItem().drawType = GL_TRIANGLES;
	Building_13->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_13->transform.position.x = 60.0f;
	Building_13->transform.position.z = 0.0f;
	Building_13->GetRenderItem().isLocalTwoSide = true;
	Building_13->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_13);
	this->objects.emplace_back(Building_13);
	this->parent->AddChild(Building_13);

	auto collision_13 = new CollisionBox(this, "building");
	collision_13->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_13->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_13);
	this->objects.emplace_back(collision_13);
	Building_13->AddChild(collision_13);

	auto Building_14 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_14->GetRenderItem().drawType = GL_TRIANGLES;
	Building_14->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_14->transform.position.x = 10.0f;
	Building_14->transform.position.z = -50.0f;
	Building_14->GetRenderItem().isLocalTwoSide = true;
	Building_14->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_14);
	this->objects.emplace_back(Building_14);
	this->parent->AddChild(Building_14);

	auto collision_14 = new CollisionBox(this, "building");
	collision_14->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_14->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_14);
	this->objects.emplace_back(collision_14);
	Building_14->AddChild(collision_14);

	auto Building_15 = new GameObject(this, currentShaderProgram, "building2", "building2_diff");
	Building_15->GetRenderItem().drawType = GL_TRIANGLES;
	Building_15->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_15->transform.position.x = 25.0f;
	Building_15->transform.position.z = -42.0f;
	Building_15->GetRenderItem().isLocalTwoSide = true;
	Building_15->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_15);
	this->objects.emplace_back(Building_15);
	this->parent->AddChild(Building_15);

	auto collision_15 = new CollisionBox(this, "building");
	collision_15->transform.position = glm::vec3(0.0f, 2.75f, 0.0f);
	collision_15->transform.scale = glm::vec3(5.8f, 3.1f, 3.8f);
	this->collisionObjects.emplace_back(collision_15);
	this->objects.emplace_back(collision_15);
	Building_15->AddChild(collision_15);

	auto Building_16 = new GameObject(this, currentShaderProgram, "building3", "building3_diff");
	Building_16->GetRenderItem().drawType = GL_TRIANGLES;
	Building_16->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_16->transform.position.x = 30.0f;
	Building_16->transform.position.z = 15.0f;
	Building_16->GetRenderItem().isLocalTwoSide = true;
	Building_16->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_16);
	this->objects.emplace_back(Building_16);
	this->parent->AddChild(Building_16);

	auto collision_16 = new CollisionBox(this, "building");
	collision_16->transform.position = glm::vec3(+0.5f, 3.0f, 0.7f);
	collision_16->transform.scale = glm::vec3(3.0f, 3.5f, 4.35f);
	this->collisionObjects.emplace_back(collision_16);
	this->objects.emplace_back(collision_16);
	Building_16->AddChild(collision_16);

	auto Building_17 = new GameObject(this, currentShaderProgram, "building4", "building4_diff");
	Building_17->GetRenderItem().drawType = GL_TRIANGLES;
	Building_17->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_17->transform.position.x = 45.0f;
	Building_17->transform.position.z = 7.0f;
	Building_17->GetRenderItem().isLocalTwoSide = true;
	Building_17->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_17);
	this->objects.emplace_back(Building_17);
	this->parent->AddChild(Building_17);

	auto collision_17 = new CollisionBox(this, "building");
	collision_17->transform.position = glm::vec3(-0.2f, 3.2f, 0.1f);
	collision_17->transform.scale = glm::vec3(4.7f, 3.8f, 4.2f);
	this->collisionObjects.emplace_back(collision_17);
	this->objects.emplace_back(collision_17);
	Building_17->AddChild(collision_17);

	auto Building_18 = new GameObject(this, currentShaderProgram, "building5", "building5_diff");
	Building_18->GetRenderItem().drawType = GL_TRIANGLES;
	Building_18->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_18->transform.position.x = 65.0f;
	Building_18->transform.position.z = 15.0f;
	Building_18->GetRenderItem().isLocalTwoSide = true;
	Building_18->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_18);
	this->objects.emplace_back(Building_18);
	this->parent->AddChild(Building_18);

	auto collision_18 = new CollisionBox(this, "building");
	collision_18->transform.position = glm::vec3(-0.2f, 4.5f, 0.2f);
	collision_18->transform.scale = glm::vec3(4.5f, 4.8f, 4.35f);
	this->collisionObjects.emplace_back(collision_18);
	this->objects.emplace_back(collision_18);
	Building_18->AddChild(collision_18);

	auto Building_19 = new GameObject(this, currentShaderProgram, "building6", "building6_diff");
	Building_19->GetRenderItem().drawType = GL_TRIANGLES;
	Building_19->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_19->transform.position.x = 35.0f;
	Building_19->transform.position.z = 35.0f;
	Building_19->GetRenderItem().isLocalTwoSide = true;
	Building_19->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_19);
	this->objects.emplace_back(Building_19);
	this->parent->AddChild(Building_19);

	auto collision_19 = new CollisionBox(this, "building");
	collision_19->transform.position = glm::vec3(0.0f, 8.2f, 0.4f);
	collision_19->transform.scale = glm::vec3(7.8f, 8.5f, 6.45f);
	this->collisionObjects.emplace_back(collision_19);
	this->objects.emplace_back(collision_19);
	Building_19->AddChild(collision_19);

	auto Building_20 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_20->GetRenderItem().drawType = GL_TRIANGLES;
	Building_20->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_20->transform.position.x = 55.0f;
	Building_20->transform.position.z = 60.0f;
	Building_20->GetRenderItem().isLocalTwoSide = true;
	Building_20->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_20);
	this->objects.emplace_back(Building_20);
	this->parent->AddChild(Building_20);

	auto collision_20 = new CollisionBox(this, "building");
	collision_20->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_20->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_20);
	this->objects.emplace_back(collision_20);
	Building_20->AddChild(collision_20);

	auto Building_21 = new GameObject(this, currentShaderProgram, "building2", "building2_diff");
	Building_21->GetRenderItem().drawType = GL_TRIANGLES;
	Building_21->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_21->transform.position.x = 60.0f;
	Building_21->transform.position.z = 32.0f;
	Building_21->GetRenderItem().isLocalTwoSide = true;
	Building_21->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_21);
	this->objects.emplace_back(Building_21);
	this->parent->AddChild(Building_21);

	auto collision_21 = new CollisionBox(this, "building");
	collision_21->transform.position = glm::vec3(0.0f, 2.75f, 0.0f);
	collision_21->transform.scale = glm::vec3(5.8f, 3.1f, 3.8f);
	this->collisionObjects.emplace_back(collision_21);
	this->objects.emplace_back(collision_21);
	Building_21->AddChild(collision_21);

	auto Building_22 = new GameObject(this, currentShaderProgram, "building3", "building3_diff");
	Building_22->GetRenderItem().drawType = GL_TRIANGLES;
	Building_22->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_22->transform.position.x = 45.0f;
	Building_22->transform.position.z = 45.0f;
	Building_22->GetRenderItem().isLocalTwoSide = true;
	Building_22->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_22);
	this->objects.emplace_back(Building_22);
	this->parent->AddChild(Building_22);

	auto collision_22 = new CollisionBox(this, "building");
	collision_22->transform.position = glm::vec3(+0.5f, 3.0f, 0.7f);
	collision_22->transform.scale = glm::vec3(3.0f, 3.5f, 4.35f);
	this->collisionObjects.emplace_back(collision_22);
	this->objects.emplace_back(collision_22);
	Building_22->AddChild(collision_22);

	auto Building_23 = new GameObject(this, currentShaderProgram, "building4", "building4_diff");
	Building_23->GetRenderItem().drawType = GL_TRIANGLES;
	Building_23->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_23->transform.position.x = -2.0f;
	Building_23->transform.position.z = 15.0f;
	Building_23->GetRenderItem().isLocalTwoSide = true;
	Building_23->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_23);
	this->objects.emplace_back(Building_23);
	this->parent->AddChild(Building_23);

	auto collision_23 = new CollisionBox(this, "building");
	collision_23->transform.position = glm::vec3(-0.2f, 3.2f, 0.1f);
	collision_23->transform.scale = glm::vec3(4.7f, 3.8f, 4.2f);
	this->collisionObjects.emplace_back(collision_23);
	this->objects.emplace_back(collision_23);
	Building_23->AddChild(collision_23);

	auto Building_24 = new GameObject(this, currentShaderProgram, "building5", "building5_diff");
	Building_24->GetRenderItem().drawType = GL_TRIANGLES;
	Building_24->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_24->transform.position.x = 5.0f;
	Building_24->transform.position.z = 32.0f;
	Building_24->GetRenderItem().isLocalTwoSide = true;
	Building_24->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_24);
	this->objects.emplace_back(Building_24);
	this->parent->AddChild(Building_24);

	auto collision_24 = new CollisionBox(this, "building");
	collision_24->transform.position = glm::vec3(-0.2f, 4.5f, 0.2f);
	collision_24->transform.scale = glm::vec3(4.5f, 4.8f, 4.35f);
	this->collisionObjects.emplace_back(collision_24);
	this->objects.emplace_back(collision_24);
	Building_24->AddChild(collision_24);

	auto Building_25 = new GameObject(this, currentShaderProgram, "building6", "building6_diff");
	Building_25->GetRenderItem().drawType = GL_TRIANGLES;
	Building_25->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_25->transform.position.x = -5.0f;
	Building_25->transform.position.z = 45.0f;
	Building_25->GetRenderItem().isLocalTwoSide = true;
	Building_25->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_25);
	this->objects.emplace_back(Building_25);
	this->parent->AddChild(Building_25);

	auto collision_25 = new CollisionBox(this, "building");
	collision_25->transform.position = glm::vec3(0.0f, 8.2f, 0.4f);
	collision_25->transform.scale = glm::vec3(7.8f, 8.5f, 6.45f);
	this->collisionObjects.emplace_back(collision_25);
	this->objects.emplace_back(collision_25);
	Building_25->AddChild(collision_25);

	auto Building_26 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_26->GetRenderItem().drawType = GL_TRIANGLES;
	Building_26->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_26->transform.position.x = -18.0f;
	Building_26->transform.position.z = 30.0f;
	Building_26->GetRenderItem().isLocalTwoSide = true;
	Building_26->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_26);
	this->objects.emplace_back(Building_26);
	this->parent->AddChild(Building_26);

	auto collision_26 = new CollisionBox(this, "building");
	collision_26->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_26->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_26);
	this->objects.emplace_back(collision_26);
	Building_26->AddChild(collision_26);

	auto Building_27 = new GameObject(this, currentShaderProgram, "building2", "building2_diff");
	Building_27->GetRenderItem().drawType = GL_TRIANGLES;
	Building_27->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_27->transform.position.x = -22.0f;
	Building_27->transform.position.z = 52.0f;
	Building_27->GetRenderItem().isLocalTwoSide = true;
	Building_27->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_27);
	this->objects.emplace_back(Building_27);
	this->parent->AddChild(Building_27);

	auto collision_27 = new CollisionBox(this, "building");
	collision_27->transform.position = glm::vec3(0.0f, 2.75f, 0.0f);
	collision_27->transform.scale = glm::vec3(5.8f, 3.1f, 3.8f);
	this->collisionObjects.emplace_back(collision_27);
	this->objects.emplace_back(collision_27);
	Building_27->AddChild(collision_27);

	auto Building_28 = new GameObject(this, currentShaderProgram, "building3", "building3_diff");
	Building_28->GetRenderItem().drawType = GL_TRIANGLES;
	Building_28->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_28->transform.position.x = -38.0f;
	Building_28->transform.position.z = 35.0f;
	Building_28->GetRenderItem().isLocalTwoSide = true;
	Building_28->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_28);
	this->objects.emplace_back(Building_28);
	this->parent->AddChild(Building_28);

	auto collision_28 = new CollisionBox(this, "building");
	collision_28->transform.position = glm::vec3(+0.5f, 3.0f, 0.7f);
	collision_28->transform.scale = glm::vec3(3.0f, 3.5f, 4.35f);
	this->collisionObjects.emplace_back(collision_28);
	this->objects.emplace_back(collision_28);
	Building_28->AddChild(collision_28);

	auto Building_29 = new GameObject(this, currentShaderProgram, "building4", "building4_diff");
	Building_29->GetRenderItem().drawType = GL_TRIANGLES;
	Building_29->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_29->transform.position.x = -49.0f;
	Building_29->transform.position.z = 22.0f;
	Building_29->GetRenderItem().isLocalTwoSide = true;
	Building_29->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(terrain);
	this->objects.emplace_back(Building_29);
	this->parent->AddChild(Building_29);

	auto collision_29 = new CollisionBox(this, "building");
	collision_29->transform.position = glm::vec3(-0.2f, 3.2f, 0.1f);
	collision_29->transform.scale = glm::vec3(4.7f, 3.8f, 4.2f);
	this->collisionObjects.emplace_back(collision_29);
	this->objects.emplace_back(collision_29);
	Building_29->AddChild(collision_29);

	auto Building_30 = new GameObject(this, currentShaderProgram, "building5", "building5_diff");
	Building_30->GetRenderItem().drawType = GL_TRIANGLES;
	Building_30->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_30->transform.position.x = -56.0f;
	Building_30->transform.position.z = 35.0f;
	Building_30->GetRenderItem().isLocalTwoSide = true;
	Building_30->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_30);
	this->objects.emplace_back(Building_30);
	this->parent->AddChild(Building_30);

	auto collision_30 = new CollisionBox(this, "building");
	collision_30->transform.position = glm::vec3(-0.2f, 4.5f, 0.2f);
	collision_30->transform.scale = glm::vec3(4.5f, 4.8f, 4.35f);
	this->collisionObjects.emplace_back(collision_30);
	this->objects.emplace_back(collision_30);
	Building_30->AddChild(collision_30);

	auto Building_31 = new GameObject(this, currentShaderProgram, "building6", "building6_diff");
	Building_31->GetRenderItem().drawType = GL_TRIANGLES;
	Building_31->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_31->transform.position.x = -46.0f;
	Building_31->transform.position.z = 50.0f;
	Building_31->GetRenderItem().isLocalTwoSide = true;
	Building_31->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_31);
	this->objects.emplace_back(Building_31);
	this->parent->AddChild(Building_31);

	auto collision_31 = new CollisionBox(this, "building");
	collision_31->transform.position = glm::vec3(0.0f, 8.2f, 0.4f);
	collision_31->transform.scale = glm::vec3(7.8f, 8.5f, 6.45f);
	this->collisionObjects.emplace_back(collision_31);
	this->objects.emplace_back(collision_31);
	Building_31->AddChild(collision_31);

	auto Building_32 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_32->GetRenderItem().drawType = GL_TRIANGLES;
	Building_32->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_32->transform.position.x = -27.0f;
	Building_32->transform.position.z = 15.0f;
	Building_32->GetRenderItem().isLocalTwoSide = true;
	Building_32->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_32);
	this->objects.emplace_back(Building_32);
	this->parent->AddChild(Building_32);

	auto collision_32 = new CollisionBox(this, "building");
	collision_32->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_32->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_32);
	this->objects.emplace_back(collision_32);
	Building_32->AddChild(collision_32);

	auto Building_33 = new GameObject(this, currentShaderProgram, "building6", "building6_diff");
	Building_33->GetRenderItem().drawType = GL_TRIANGLES;
	Building_33->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_33->transform.position.x = -55.0f;
	Building_33->transform.position.z = 3.0f;
	Building_33->GetRenderItem().isLocalTwoSide = true;
	Building_33->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_33);
	this->objects.emplace_back(Building_33);
	this->parent->AddChild(Building_33);

	auto collision_33 = new CollisionBox(this, "building");
	collision_33->transform.position = glm::vec3(0.0f, 8.2f, 0.4f);
	collision_33->transform.scale = glm::vec3(7.8f, 8.5f, 6.45f);
	this->collisionObjects.emplace_back(collision_33);
	this->objects.emplace_back(collision_33);
	Building_33->AddChild(collision_33);

	auto Building_34 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_34->GetRenderItem().drawType = GL_TRIANGLES;
	Building_34->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_34->transform.position.x = -15.0f;
	Building_34->transform.position.z = -15.0f;
	Building_34->GetRenderItem().isLocalTwoSide = true;
	Building_34->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_34);
	this->objects.emplace_back(Building_34);
	this->parent->AddChild(Building_34);

	auto collision_34 = new CollisionBox(this, "building");
	collision_34->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_34->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_34);
	this->objects.emplace_back(collision_34);
	Building_34->AddChild(collision_34);

	auto Building_35 = new GameObject(this, currentShaderProgram, "building2", "building2_diff");
	Building_35->GetRenderItem().drawType = GL_TRIANGLES;
	Building_35->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_35->transform.position.x = -32.0f;
	Building_35->transform.position.z = -18.0f;
	Building_35->GetRenderItem().isLocalTwoSide = true;
	Building_35->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_35);
	this->objects.emplace_back(Building_35);
	this->parent->AddChild(Building_35);

	auto collision_35 = new CollisionBox(this, "building");
	collision_35->transform.position = glm::vec3(0.0f, 2.75f, 0.0f);
	collision_35->transform.scale = glm::vec3(5.8f, 3.1f, 3.8f);
	this->collisionObjects.emplace_back(collision_35);
	this->objects.emplace_back(collision_35);
	Building_35->AddChild(collision_35);

	auto Building_36 = new GameObject(this, currentShaderProgram, "building3", "building3_diff");
	Building_36->GetRenderItem().drawType = GL_TRIANGLES;
	Building_36->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_36->transform.position.x = -48.0f;
	Building_36->transform.position.z = -12.0f;
	Building_36->GetRenderItem().isLocalTwoSide = true;
	Building_36->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_36);
	this->objects.emplace_back(Building_36);
	this->parent->AddChild(Building_36);

	auto collision_36 = new CollisionBox(this, "building");
	collision_36->transform.position = glm::vec3(+0.5f, 3.0f, 0.7f);
	collision_36->transform.scale = glm::vec3(3.0f, 3.5f, 4.35f);
	this->collisionObjects.emplace_back(collision_36);
	this->objects.emplace_back(collision_36);
	Building_36->AddChild(collision_36);

	auto Building_37 = new GameObject(this, currentShaderProgram, "building4", "building4_diff");
	Building_37->GetRenderItem().drawType = GL_TRIANGLES;
	Building_37->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_37->transform.position.x = -58.0f;
	Building_37->transform.position.z = -25.0f;
	Building_37->GetRenderItem().isLocalTwoSide = true;
	Building_37->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_37);
	this->objects.emplace_back(Building_37);
	this->parent->AddChild(Building_37);

	auto collision_37 = new CollisionBox(this, "building");
	collision_37->transform.position = glm::vec3(-0.2f, 3.2f, 0.1f);
	collision_37->transform.scale = glm::vec3(4.7f, 3.8f, 4.2f);
	this->collisionObjects.emplace_back(collision_37);
	this->objects.emplace_back(collision_37);
	Building_37->AddChild(collision_37);

	auto Building_38 = new GameObject(this, currentShaderProgram, "building5", "building5_diff");
	Building_38->GetRenderItem().drawType = GL_TRIANGLES;
	Building_38->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_38->transform.position.x = -42.0f;
	Building_38->transform.position.z = -33.0f;
	Building_38->GetRenderItem().isLocalTwoSide = true;
	Building_38->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_38);
	this->objects.emplace_back(Building_38);
	this->parent->AddChild(Building_38);

	auto collision_38 = new CollisionBox(this, "building");
	collision_38->transform.position = glm::vec3(-0.2f, 4.5f, 0.2f);
	collision_38->transform.scale = glm::vec3(4.5f, 4.8f, 4.35f);
	this->collisionObjects.emplace_back(collision_38);
	this->objects.emplace_back(collision_38);
	Building_38->AddChild(collision_38);

	auto Building_39 = new GameObject(this, currentShaderProgram, "building6", "building6_diff");
	Building_39->GetRenderItem().drawType = GL_TRIANGLES;
	Building_39->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_39->transform.position.x = -28.0f;
	Building_39->transform.position.z = -35.0f;
	Building_39->GetRenderItem().isLocalTwoSide = true;
	Building_39->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_39);
	this->objects.emplace_back(Building_39);
	this->parent->AddChild(Building_39);

	auto collision_39 = new CollisionBox(this, "building");
	collision_39->transform.position = glm::vec3(0.0f, 8.2f, 0.4f);
	collision_39->transform.scale = glm::vec3(7.8f, 8.5f, 6.45f);
	this->collisionObjects.emplace_back(collision_39);
	this->objects.emplace_back(collision_39);
	Building_39->AddChild(collision_39);

	auto Building_40 = new GameObject(this, currentShaderProgram, "building1", "building1_diff");
	Building_40->GetRenderItem().drawType = GL_TRIANGLES;
	Building_40->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
	Building_40->transform.position.x = -60.0f;
	Building_40->transform.position.z = -45.0f;
	Building_40->GetRenderItem().isLocalTwoSide = true;
	Building_40->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 1.0f);
	this->opaqueObjects.emplace_back(Building_40);
	this->objects.emplace_back(Building_40);
	this->parent->AddChild(Building_40);

	auto collision_40 = new CollisionBox(this, "building");
	collision_40->transform.position = glm::vec3(+0.95f, 4.9f, -0.25f);
	collision_40->transform.scale = glm::vec3(4.55f, 4.8f, 4.0f);
	this->collisionObjects.emplace_back(collision_40);
	this->objects.emplace_back(collision_40);
	Building_40->AddChild(collision_40);

}