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

#include <glm/gtx/spline.hpp>


std::vector<glm::vec4> line(300);
glm::vec3 PointOfImfact;

static float power = 0.0f;
static float xpower;
static float ypower;

static float velocity = 0.5f;
static bool isLaunch = false;
static bool isCharge = false;
static bool isIncreaseAngle = false;
static bool isDecreaseAngle = false;
static bool isRotateLeft = false;
static bool isRotateRight = false;
static bool isBombCam = false;
static bool WaitTimer = false;
static float InitTimer = 0;
static bool isBombExplosion = false;
static bool isBombExplosion2 = false;
static int targetCount = 7;
static int fireCount = 0;

float DestOrthoTop = 0;
float DestOrthoBottom = 0;
float DestOrthoLeft = 0;
float DestOrthoRight = 0;

static constexpr float markerHeight = 90.0f;

glm::vec3 lineCalc(float power, float angle)
{
	float dx;
	float dy;
	float x = 0.0;
	float y = 3.0;
	float temp;
	line.clear();
	dx = power * cos(angle * 3.14 / 180);
	dy = power * sin(angle * 3.14 / 180);

	line.push_back(glm::vec4(0, 3.0, 0, 1.0));

	for (size_t i = 0; y >= 0.0; i++)
	{
		dy -= 9.8 * 0.1f;

		if (line.size() > 2) {
			if (y > dy * 0.1) {
				y += dy * 0.1;
				x += dx * 0.1;
			}
			else {
				temp = y / dy;
				y = 0;
				x += dx * temp * 0.1;
			}
		}
		else {
			y += dy * 0.1;
			x += dx * 0.1;
		}

		line.push_back(glm::vec4(x, y, 0, 1.0));
	}
	if (line.size() % 2 == 1) {
		line.push_back(glm::vec4(x, y, 0, 1.0));
	}
	return glm::vec3(x, 0, 0.0);
}


void Framework::BuildGameObjects()
{
	this->minimapSize = glm::vec2(177 * 2.0, 100 * 2.0);
	this->uiBoard.SetVariable("target_count", targetCount);
	this->uiBoard.SetVariable("fire_count", fireCount);

#pragma region Effect


	auto getEffect = [](glm::vec3 _position, Framework* framework)
	{



		auto billboard = new LambdaGameObject(framework, framework->shaderPrograms["default"], "plane", "exp");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->GetRenderItem().objectColor = Color::White;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.rotation.y = 90.0f;
		billboard->transform.position = _position;
		billboard->transform.position.y += 5.0f;
		billboard->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1 / 8.0f));
		framework->lightObjects["expLight"]->transform.position = _position;
		framework->lightObjects["expLight"]->transform.position +=
			framework->lightObjects["expLight"]->transform.Up() * 1.0f;
		billboard->PostUpdateFunction(
			[framework](float deltaTime, LambdaGameObject* self)
			{
				self->transform.localRotate = glm::mat3(framework->constant.viewTransform.variable);
				self->transform.localRotate = glm::inverse(self->transform.localRotate);

				static size_t frame = 0;
				static size_t frameMax = 8;
				static float term = 1.0f;
				static float nowTime = 0.025f;
				static float frameTime = 0.025f;
				static float lightStrenth[10] = {0.0, 0.5, 1.0, 0.75,0.5,0.25,0.1,0.05,0.0,0.0 };
				float t = (frameTime * frame + nowTime) / (frameTime * frameMax);
				t = soy_clamp(t - frame / 8,0.0f,1.0f);
				//framework->lightObjects["expLight"]->lightStrength =
				//	glm::mix(lightStrenth[frame / 8], lightStrenth[(frame / 8) + 1],
				//		t);
				auto value = glm::catmullRom(
					glm::vec2(0,lightStrenth[(frame / 8) + 0]),
					glm::vec2(1,lightStrenth[(frame / 8) + 1]),
					glm::vec2(2,lightStrenth[(frame / 8) + 2]),
					glm::vec2(3,lightStrenth[(frame / 8) + 3]),
					t);
				framework->lightObjects["expLight"]->lightStrength = value.y;


				self->GetRenderItem().textureTrasform =
					glm::scale(glm::vec3(1.0f / 8.0f)) *
					glm::translate(glm::vec3((term) * (frame % frameMax), (term) * 7 - (term) * (frame / frameMax), 0.0f));
				nowTime -= deltaTime;
				if (nowTime <= 0.0f)
				{
					nowTime = frameTime;
					frame++;
					if (frame >= (frameMax * frameMax))
					{
						self->Destory();
						frame = 0;
					}
					frame = frame % (frameMax * frameMax);
				}

			}
		);
		billboard->PostDrawFunction(
			[framework](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(framework->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		framework->transparentObjects.emplace_back(billboard);
		framework->objects.emplace_back(billboard);
		framework->parent->AddChild(billboard);

	};

#pragma endregion


	this->constant.viewTransform = glm::lookAt(glm::vec3(0, 0.2f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0, 1.0f, 0.0f));
	this->constant.projTransform = glm::perspective(45.0f, this->aspect, 0.1f, 1000.0f);
	this->constant.ambientLight = glm::vec4(glm::vec3(0.1f), 1.0f);
	this->minimapConstant.ambientLight = glm::vec4(glm::vec3(0.15f), 1.0f);

	auto pt = new GameObject(this, this->currentShaderProgram);
	this->parent = pt;
	this->objects.emplace_back(pt);

	this->BuildMapObjects();




	auto Target = new GameObject(this, currentShaderProgram, "target");
	Target->GetRenderItem().drawType = GL_TRIANGLES;
	Target->GetRenderItem().objectColor = Color::Red;
	Target->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	Target->transform.position.x = 10.0f;
	Target->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(Target);
	this->objects.emplace_back(Target);
	this->parent->AddChild(Target);

	auto collision_1 = new CollisionBox(this, "target");
	collision_1->transform.position = glm::vec3(0,7.5f,0);
	collision_1->transform.scale = glm::vec3(1.5,1.5,1.5);
	this->collisionObjects.emplace_back(collision_1);
	this->objects.emplace_back(collision_1);
	Target->AddChild(collision_1);

	{
		auto billboard = new LambdaGameObject(this, this->shaderPrograms["clip"], "plane", "marker");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.position.y = markerHeight;
		billboard->PostDrawFunction(
			[this](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(this->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		this->transparentObjects.emplace_back(billboard);
		this->objects.emplace_back(billboard);
		Target->AddChild(billboard);
	}


	auto Target2 = new GameObject(this, currentShaderProgram, "target");
	Target2->GetRenderItem().drawType = GL_TRIANGLES;
	Target2->GetRenderItem().objectColor = Color::Red;
	Target2->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	Target2->transform.position.x = 20.0f;
	Target2->transform.position.z = 20.0f;
	Target2->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(Target2);
	this->objects.emplace_back(Target2);
	this->parent->AddChild(Target2);

	auto collision_2 = new CollisionBox(this, "target");
	collision_2->transform.position = glm::vec3(0, 7.5f, 0);
	collision_2->transform.scale = glm::vec3(1.5, 1.5, 1.5);
	this->collisionObjects.emplace_back(collision_2);
	this->objects.emplace_back(collision_2);
	Target2->AddChild(collision_2);

	{
		auto billboard = new LambdaGameObject(this, this->shaderPrograms["clip"], "plane", "marker");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.position.y = markerHeight;
		billboard->PostDrawFunction(
			[this](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(this->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		this->transparentObjects.emplace_back(billboard);
		this->objects.emplace_back(billboard);
		Target2->AddChild(billboard);
	}


	auto Target3 = new GameObject(this, currentShaderProgram, "target");
	Target3->GetRenderItem().drawType = GL_TRIANGLES;
	Target3->GetRenderItem().objectColor = Color::Red;
	Target3->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	Target3->transform.position.x = 43.0f;
	Target3->transform.position.z = -28.0f;
	Target3->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(Target3);
	this->objects.emplace_back(Target3);
	this->parent->AddChild(Target3);

	auto collision_3 = new CollisionBox(this, "target");
	collision_3->transform.position = glm::vec3(0, 7.5f, 0);
	collision_3->transform.scale = glm::vec3(1.5, 1.5, 1.5);
	this->collisionObjects.emplace_back(collision_3);
	this->objects.emplace_back(collision_3);
	Target3->AddChild(collision_3);
	{
		auto billboard = new LambdaGameObject(this, this->shaderPrograms["clip"], "plane", "marker");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.position.y = markerHeight;
		billboard->PostDrawFunction(
			[this](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(this->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		this->transparentObjects.emplace_back(billboard);
		this->objects.emplace_back(billboard);
		Target3->AddChild(billboard);
	}


	auto Target4 = new GameObject(this, currentShaderProgram, "target");
	Target4->GetRenderItem().drawType = GL_TRIANGLES;
	Target4->GetRenderItem().objectColor = Color::Red;
	Target4->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	Target4->transform.position.x = -13.0f;
	Target4->transform.position.z = -35.0f;
	Target4->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(Target4);
	this->objects.emplace_back(Target4);
	this->parent->AddChild(Target4);

	{
		auto billboard = new LambdaGameObject(this, this->shaderPrograms["clip"], "plane", "marker");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.position.y = markerHeight;
		billboard->PostDrawFunction(
			[this](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(this->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		this->transparentObjects.emplace_back(billboard);
		this->objects.emplace_back(billboard);
		Target4->AddChild(billboard);
	}

	auto collision_4 = new CollisionBox(this, "target");
	collision_4->transform.position = glm::vec3(0, 7.5f, 0);
	collision_4->transform.scale = glm::vec3(1.5, 1.5, 1.5);
	this->collisionObjects.emplace_back(collision_4);
	this->objects.emplace_back(collision_4);
	Target4->AddChild(collision_4);

	auto Target5 = new GameObject(this, currentShaderProgram, "target");
	Target5->GetRenderItem().drawType = GL_TRIANGLES;
	Target5->GetRenderItem().objectColor = Color::Red;
	Target5->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	Target5->transform.position.x = 45.0f;
	Target5->transform.position.z = 22.0f;
	Target5->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(Target5);
	this->objects.emplace_back(Target5);
	this->parent->AddChild(Target5);

	auto collision_5 = new CollisionBox(this, "target");
	collision_5->transform.position = glm::vec3(0, 7.5f, 0);
	collision_5->transform.scale = glm::vec3(1.5, 1.5, 1.5);
	this->collisionObjects.emplace_back(collision_5);
	this->objects.emplace_back(collision_5);
	Target5->AddChild(collision_5);

	{
		auto billboard = new LambdaGameObject(this, this->shaderPrograms["clip"], "plane", "marker");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.position.y = markerHeight;
		billboard->PostDrawFunction(
			[this](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(this->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		this->transparentObjects.emplace_back(billboard);
		this->objects.emplace_back(billboard);
		Target5->AddChild(billboard);
	}

	auto Target6 = new GameObject(this, currentShaderProgram, "target");
	Target6->GetRenderItem().drawType = GL_TRIANGLES;
	Target6->GetRenderItem().objectColor = Color::Red;
	Target6->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	Target6->transform.position.x = -42.0f;
	Target6->transform.position.z = -5.0f;
	Target6->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(Target6);
	this->objects.emplace_back(Target6);
	this->parent->AddChild(Target6);

	auto collision_6 = new CollisionBox(this, "target");
	collision_6->transform.position = glm::vec3(0, 7.5f, 0);
	collision_6->transform.scale = glm::vec3(1.5, 1.5, 1.5);
	this->collisionObjects.emplace_back(collision_6);
	this->objects.emplace_back(collision_6);
	Target6->AddChild(collision_6);

	{
		auto billboard = new LambdaGameObject(this, this->shaderPrograms["clip"], "plane", "marker");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.position.y = markerHeight;
		billboard->PostDrawFunction(
			[this](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(this->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		this->transparentObjects.emplace_back(billboard);
		this->objects.emplace_back(billboard);
		Target6->AddChild(billboard);
	}


	auto Target7 = new GameObject(this, currentShaderProgram, "target");
	Target7->GetRenderItem().drawType = GL_TRIANGLES;
	Target7->GetRenderItem().objectColor = Color::Red;
	Target7->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
	Target7->transform.position.x = -30.0f;
	Target7->transform.position.z = 25.0f;
	Target7->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 5.0f);
	this->opaqueObjects.emplace_back(Target7);
	this->objects.emplace_back(Target7);
	this->parent->AddChild(Target7);

	auto collision_7 = new CollisionBox(this, "target");
	collision_7->transform.position = glm::vec3(0, 7.5f, 0);
	collision_7->transform.scale = glm::vec3(1.5, 1.5, 1.5);
	this->collisionObjects.emplace_back(collision_7);
	this->objects.emplace_back(collision_7);
	Target7->AddChild(collision_7);


	{
		auto billboard = new LambdaGameObject(this, this->shaderPrograms["clip"], "plane", "marker");
		billboard->GetRenderItem().drawType = GL_TRIANGLES;
		billboard->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
		billboard->transform.rotation.x = 90.0f;
		billboard->transform.position.y = markerHeight;
		billboard->PostDrawFunction(
			[this](LambdaGameObject* self)
			{
				self->transform.localRotate = glm::inverse(glm::mat3(this->nowConstant->viewTransform.variable));
				self->GetRenderItem().worldTrasform = self->transform.parentTransform * self->transform.GetMaxtrix();
			}
		);
		this->transparentObjects.emplace_back(billboard);
		this->objects.emplace_back(billboard);
		Target7->AddChild(billboard);
	}

	auto cannonbase = new LambdaGameObject(this, currentShaderProgram, "cannonbase", "bricks");
	cannonbase->GetRenderItem().drawType = GL_TRIANGLES;
	cannonbase->GetRenderItem().objectColor = Color::White;
	cannonbase->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.3f;
	cannonbase->GetRenderItem().textureTrasform = glm::scale(glm::vec3(1.0f) * 0.1f);
	cannonbase->transform.position.y = 0.0;
	cannonbase->PostSpecialFunction(
		[](int key, int x, int y, LambdaGameObject* self)
		{
			if (!isCharge && !isLaunch && !WaitTimer) {
				switch (key)
				{
				case GLUT_KEY_LEFT:
				{
					isRotateLeft = true;
				}
				break;

				case GLUT_KEY_RIGHT:
				{
					isRotateRight = true;
				}
				break;
				default:
					break;
				}
			}
		}
	);
	cannonbase->PostSpecialUpFunction(
		[](int key, int x, int y, LambdaGameObject* self)
		{
			switch (key)
			{
			case GLUT_KEY_LEFT:
			{
				isRotateLeft = false;
			}
			break;
			case GLUT_KEY_RIGHT:
			{
				isRotateRight = false;
			}
			break;
			default:
				break;
			}
		}
	);
	cannonbase->PostUpdateFunction(
		[](float deltaTime, LambdaGameObject* self)
		{
			if (isRotateLeft) {
				self->transform.rotation.y += 20 * deltaTime;
			}
			if (isRotateRight) {
				self->transform.rotation.y -= 20 * deltaTime;
			}
		}
	);
	this->opaqueObjects.emplace_back(cannonbase);
	this->objects.emplace_back(cannonbase);
	this->parent->AddChild(cannonbase);


	auto Rotator = new GameObject(this, currentShaderProgram, "plane", "rotator");
	Rotator->GetRenderItem().drawType = GL_TRIANGLES;
	Rotator->GetRenderItem().isLocalTwoSide = true;
	Rotator->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 10.0f;
	Rotator->transform.position.y = 300.0f;
	Rotator->transform.rotation.y = -90.0f;
	this->transparentObjects.emplace_back(Rotator);
	this->objects.emplace_back(Rotator);
	cannonbase->AddChild(Rotator);



	auto cannonbarrel = new LambdaGameObject(this, currentShaderProgram, "cannonbarrel");
	cannonbarrel->GetRenderItem().drawType = GL_TRIANGLES;
	cannonbarrel->GetRenderItem().objectColor = Color::Black;
	cannonbarrel->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	cannonbarrel->transform.position.y = 0.0;
	cannonbarrel->transform.rotation.z = 10.0;
	cannonbarrel->PostSpecialFunction(
		[](int key, int x, int y, LambdaGameObject* self)
		{
			switch (key)
			{
			case GLUT_KEY_UP:
			{
				isIncreaseAngle = true;
			}
			break;
			case GLUT_KEY_DOWN:
			{
				isDecreaseAngle = true;
			}
			break;
			default:
				break;
			}
		}
	);
	cannonbarrel->PostSpecialUpFunction(
		[](unsigned char key, int x, int y, LambdaGameObject* self)
		{
			switch (key)
			{
			case GLUT_KEY_UP:
			{
				isIncreaseAngle = false;
			}
			break;
			case GLUT_KEY_DOWN:
			{
				isDecreaseAngle = false;
			}
			break;
			default:
				break;
			}
		}
	);
	cannonbarrel->PostUpdateFunction(
		[](float deltaTime, LambdaGameObject* self)
		{
			if (isIncreaseAngle) {
				self->transform.rotation.z += 20.0f * deltaTime;
				self->transform.rotation.z = soy_clamp(self->transform.rotation.z, 0.0f, 90.0f);
				if (!isLaunch) {
					xpower = power * cos(self->transform.rotation.z * 3.14 / 180);
					ypower = power * sin(self->transform.rotation.z * 3.14 / 180);
				}
			}
			if (isDecreaseAngle) {
				self->transform.rotation.z -= 20.0f * deltaTime;
				self->transform.rotation.z = soy_clamp(self->transform.rotation.z, 0.0f, 90.0f);
				if (!isLaunch) {
					xpower = power * cos(self->transform.rotation.z * 3.14 / 180);
					ypower = power * sin(self->transform.rotation.z * 3.14 / 180);
				}
			}
		}
	);
	this->opaqueObjects.emplace_back(cannonbarrel);
	this->objects.emplace_back(cannonbarrel);
	cannonbase->AddChild(cannonbarrel);

	auto bomb = new LambdaGameObject(this, currentShaderProgram, "bomb");
	bomb->transform.position.y = 5.0;
	bomb->transform.rotation.z = -75;
	bomb->GetRenderItem().drawType = GL_TRIANGLES;
	bomb->GetRenderItem().objectColor = Color::Black;
	bomb->PostKeyFunction(
		[this](unsigned char key, int x, int y, LambdaGameObject* self)
		{
			switch (key)
			{
			case ' ':
			{
				if (!isLaunch && !isCharge && !WaitTimer) {
					self->transform.position.x = 0.0;
					self->transform.position.y = 3.0;
					InitTimer = 0;
					isBombExplosion = false;
					isCharge = true;
					isRotateLeft = false;
					isRotateRight = false;
				}
			}
			break;
			default:
				break;
			}
		}
	);
	bomb->PostKeyUpFunction(
		[this](unsigned char key, int x, int y, LambdaGameObject* self)
		{
			switch (key)
			{
			case ' ':
			{
				if (!isLaunch && !WaitTimer && isCharge) {
					fireCount += 1;
					this->uiBoard.SetVariable("fire_count", fireCount);
					isLaunch = true;
					isCharge = false;
					this->PlaySound("fire");
				}
			}
			break;
			default:
				break;
			}
		}
	);
	bomb->PostUpdateFunction(
		[cannonbarrel, &getEffect, this](float deltaTime, LambdaGameObject* self)
		{
			this->uiBoard.SetVariable("cannon_power", power);
			if (self->transform.position.x > 320) {
				isBombExplosion = true;
				if (isBombCam) {
					isBombExplosion2 = true;
				}  
			}
			deltaTime *= 3;
			if (isCharge) {
				if (power <= 70 && power >= 0) {
					power += 20 * velocity * deltaTime;
					
				}
				else {
					velocity *= -1;
					power = soy_clamp(power, 0.0f, 70.0f);
				}
				xpower = power * cos(cannonbarrel->transform.rotation.z * 3.14 / 180);
				ypower = power * sin(cannonbarrel->transform.rotation.z * 3.14 / 180);
			}
			if (isLaunch) {
				self->isVisible = true;
				ypower -= 9.8 * deltaTime;
				self->transform.position.y += ypower * deltaTime;
				self->transform.position.x += xpower * deltaTime;
				if (self->transform.position.y < 0 || isBombExplosion) {
					this->PlaySound("explosion");
					getEffect(
						glm::vec3(self->transform.currentTransform * glm::vec4(glm::vec3(0.0f), 1.0f)), this);
					xpower = power * cos(cannonbarrel->transform.rotation.z * 3.14 / 180);
					ypower = power * sin(cannonbarrel->transform.rotation.z * 3.14 / 180);
					power = 0;
					isBombExplosion = false;
					isLaunch = false;
				}
			}
			else {
				self->isVisible = false;
			}
		}
	);
	this->opaqueObjects.emplace_back(bomb);
	this->objects.emplace_back(bomb);
	cannonbarrel->AddSibiling(bomb);

	auto bombCollision = new CollisionBox(this, "bomb");
	bombCollision->PostOnCollisionFunc(
		[this](CollisionBox* a, CollisionBox* b, glm::vec4 pos)
		{
			if ((a->phyTag == "building" && b->phyTag == "bomb") || (b->phyTag == "building" && a->phyTag == "bomb"))
			{
				isBombExplosion = true;
				if (isBombCam) {
					isBombExplosion2 = true;
				}
			}
			else if ((a->phyTag == "target" && b->phyTag == "bomb"))
			{
				isBombExplosion = true;
				if (isBombCam) {
					isBombExplosion2 = true;
				}
				targetCount -= 1;
				this->uiBoard.SetVariable("target_count", targetCount);
				a->GetParent()->Destory();
			}
			else if ((b->phyTag == "target" && a->phyTag == "bomb"))
			{
				isBombExplosion = true;
				if (isBombCam) {
					isBombExplosion2 = true;
				}
				targetCount -= 1;
				this->uiBoard.SetVariable("target_count", targetCount);
				b->GetParent()->Destory();
			}

		}
	);
	this->collisionObjects.emplace_back(bombCollision);
	this->objects.emplace_back(bombCollision);
	bomb->AddChild(bombCollision);





#pragma region Camera

	auto firstCamera = new MouseCameraObject(this);
	firstCamera->transform.position = glm::vec3(0.0f, 5.0f, 5.0f);
	firstCamera->speed = 10.0f;
	this->objects.emplace_back(firstCamera);
	this->parent->AddChild(firstCamera);
	this->cameraObjects["firstCamera"] = firstCamera;

	auto cannonCamera = new LambdaCameraObject(this);
	cannonCamera->transform.position.y = 5;
	cannonCamera->transform.position.x = -15;
	cannonCamera->transform.position.z = 0;
	cannonCamera->transform.rotation.y = -90;
	cannonCamera->PostUpdateFunction(
		[this, bomb](float deltaTime, LambdaCameraObject* self)
		{
			if (isCharge && self->transform.position.z < 2.0f) {
				self->transform.position.z += 5 * deltaTime;
			}
			else if (!isCharge && self->transform.position.z > 0) {
				self->transform.position.z -= 5 * deltaTime;
			}
			if (bomb->transform.position.y > 50) {
				WaitTimer = true;
				isBombCam = true;
				this->ChangeCamera("bombCamera");
			}
		}
	);
	this->objects.emplace_back(cannonCamera);
	cannonbase->AddChild(cannonCamera);
	this->cameraObjects["cannonCamera"] = cannonCamera;
	this->ChangeCamera("cannonCamera");

	auto bombCamera = new LambdaCameraObject(this);
	bombCamera->transform.position.y = 0;
	bombCamera->transform.position.x = -25;
	bombCamera->transform.rotation.y = -90;
	bombCamera->PostUpdateFunction(
		[this, bomb, &getEffect](float deltaTime, LambdaCameraObject* self)
		{


			if (bomb->transform.position.y < 0 || isBombExplosion2) {
				InitTimer += deltaTime;
			}

			if ((bomb->transform.position.y < 50  && isLaunch) && isBombCam) {
				self->transform.position += self->transform.Forward() * 300.0f * deltaTime;
			}
			else if (isBombExplosion2 && InitTimer < 0.3) {
				self->transform.position += self->transform.Forward() * 300.0f * deltaTime;
			}
			else if(isLaunch){
				bomb->transform.rotation.y += 45.0f * deltaTime;
			}
			else {
				bomb->transform.rotation.y += 10.0f * deltaTime;
			}
			

			if (InitTimer > 3 ) {
				self->transform.position.x = -25;
				self->transform.position.y = 0;
				bomb->transform.position.x = 0;
				bomb->transform.position.y = 3.0;
				isBombCam = false;
				WaitTimer = false;
				isBombExplosion2 = false;
				this->ChangeCamera("cannonCamera");
				InitTimer = 0;
			}
		}
	);
	this->objects.emplace_back(bombCamera);
	bomb->AddChild(bombCamera);
	this->cameraObjects["bombCamera"] = bombCamera;

	auto skyCamera = new LambdaCameraObject(this);
	skyCamera->transform.position = glm::vec3(0.0f, 100.0f, 0.0f);
	skyCamera->transform.rotation.x = -90.0f;
	skyCamera->isPerspective = false;
	skyCamera->orthoLeft = -50.0f * this->aspect;
	skyCamera->orthoRight = 50.0f * this->aspect;
	skyCamera->orthoBottom = -50.0f;
	skyCamera->orthoTop = 50.0f;
	DestOrthoLeft = skyCamera->orthoLeft;
	DestOrthoRight = skyCamera->orthoRight;
	DestOrthoBottom = skyCamera->orthoBottom;
	DestOrthoTop = skyCamera->orthoTop;

	this->objects.emplace_back(skyCamera);
	this->parent->AddChild(skyCamera);
	this->cameraObjects["skyCamera"] = skyCamera;
	this->ChangeMinimapCamera("skyCamera");
	skyCamera->PostUpdateFunction(
		[this](float deltaTime, LambdaCameraObject* self) 
		{
			if (this->currentCamera == this->cameraObjects["skyCamera"] ||
				this->currentCamera == this->cameraObjects["bombCamera"] || 
				this->currentCamera == this->cameraObjects["firstCamera"])
			{
				this->TurnOffUI();
			}
			else 
			{
				this->TurnOnUI();
			}
			self->orthoTop = glm::mix(self->orthoTop, DestOrthoTop, 0.75 * deltaTime);
			self->orthoBottom = glm::mix(self->orthoBottom, DestOrthoBottom, 0.75 * deltaTime);
			self->orthoLeft = glm::mix(self->orthoLeft, DestOrthoLeft, 0.75 * deltaTime);
			self->orthoRight = glm::mix(self->orthoRight, DestOrthoRight, 0.75 * deltaTime);
		}
	);

	skyCamera->PostKeyFunction(
		[this](unsigned char key, int x, int y, LambdaCameraObject* self) {
			static bool isFirst = true;
			if (key == '1') {
				isFirst = !isFirst;
				(isFirst) ? (this->ChangeCamera("cannonCamera")) : (this->ChangeCamera("skyCamera"));
			}
			else if (key == '2')
			{
				this->ChangeCamera("firstCamera");
			}

		});
	skyCamera->PostSpecialFunction(
		[](unsigned char key, int x, int y, LambdaCameraObject* self) {
			if (key == GLUT_KEY_PAGE_UP) {
				if (DestOrthoTop > 10) {
					DestOrthoTop *= 0.5;
					DestOrthoBottom *= 0.5;
					DestOrthoLeft *= 0.5;
					DestOrthoRight *= 0.5;
				}
			}
			if (key == GLUT_KEY_PAGE_DOWN) {
				if (DestOrthoTop < 50) {
					DestOrthoBottom *= 2;
					DestOrthoTop *= 2;
					DestOrthoLeft *= 2;
					DestOrthoRight *= 2;
				}
			}

		});

#pragma endregion


	auto skyBox = new GameObject(this, this->shaderPrograms["skybox"], "cube", "skybox");

#pragma region Light

	auto lightOne = new LightObject(this);
	constexpr float lightStr = 0.5f;
	lightOne->lightStrength = 0.5f;
	auto lightParent = new LambdaGameObject(this);
	lightParent->transform.position.y = 0;
	lightParent->PostUpdateFunction(
		[lightOne, lightStr, skyBox](float deltaTime, LambdaGameObject* self)
		{
			self->transform.rotation.x += 35.0f * deltaTime;
			lightOne->lightStrength =
				soy_clamp(glm::cos(glm::radians(self->transform.rotation.x)), 0.0f, 1.0f);

			skyBox->GetRenderItem().objectColor.variable.g = soy_clamp(
				(lightOne->lightStrength + 0.5f) * 0.8f + 0.3f,0.0f,1.0f
			);
			skyBox->GetRenderItem().objectColor.variable.b = soy_clamp
			(
				(lightOne->lightStrength + 0.5f) * 0.8f + 0.3f,0.0f,1.0f
			);
			//�����̶� ������ ��Ʈ���� 2���
		}
	);
	this->objects.emplace_back(lightParent);
	this->parent->AddChild(lightParent);

	lightOne->transform.position.y = 100.0;
	lightOne->transform.scale = glm::vec3(0.25f);
	lightOne->lightColor = Color::White;
	//lightOne->GetRenderItem().drawType = GL_TRIANGLES;
	//lightOne->GetRenderItem().objectColor = Color::White;

	this->opaqueObjects.emplace_back(lightOne);
	this->objects.emplace_back(lightOne);
	lightParent->AddChild(lightOne);
	this->lightObjects["one"] = lightOne;

	auto explosiveLight = new LightObject(this);
	explosiveLight->lightColor = Color::Red;
	explosiveLight->lightStrength = 0.0f;
	this->opaqueObjects.emplace_back(explosiveLight);
	this->objects.emplace_back(explosiveLight);
	this->parent->AddChild(explosiveLight);
	this->lightObjects["expLight"] = explosiveLight;
#pragma endregion

#pragma region LINE

	auto targetingpoint = new LambdaGameObject(this, currentShaderProgram, "targetingpoint", "lightProbe");
	targetingpoint->GetRenderItem().drawType = GL_TRIANGLES;
	targetingpoint->GetRenderItem().objectColor = Color::Red;
	targetingpoint->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.3f;
	targetingpoint->transform.rotation.x = 0.0f;
	targetingpoint->transform.position = PointOfImfact;
	targetingpoint->PostUpdateFunction(
		[](float deltaTime, LambdaGameObject* self)
		{
			if (isCharge || isLaunch) {
				self->isVisible = true;
			}
			else {
				self->isVisible = false;
			}
			self->transform.rotation.y += 3.0;
		}
	);
	this->opaqueObjects.emplace_back(targetingpoint);
	this->objects.emplace_back(targetingpoint);
	cannonbase->AddChild(targetingpoint);

	VertexArrayObject<4> line_vao;
	line_vao.Init();
	std::fill(line.begin(), line.end(), glm::vec4(glm::vec3(0.0f), 1.0f));
	line_vao.Load(0, line.data(), sizeof(float), 4, line.size());
	std::vector<glm::vec4> colors(line.size());
	std::vector<glm::vec4> normals(line.size());
	std::fill(colors.begin(), colors.end(), glm::vec4(1.0f));
	std::fill(normals.begin(), normals.end(), glm::vec4(glm::vec3(1.0f), 1.0f));
	line_vao.Load(1, colors.data(), sizeof(float), 4, colors.size());
	line_vao.Load(2, normals.data(), sizeof(float), 4, normals.size());
	this->meshes["lines"] = line_vao;

	auto lineObject = new LambdaGameObject(this, currentShaderProgram, "lines", "bounding");
	glLineWidth(5.0f);
	lineObject->GetRenderItem().drawType = GL_LINES;
	lineObject->GetRenderItem().isLocalTwoSide = true;
	lineObject->GetRenderItem().objectColor = Color::Green;
	lineObject->PostUpdateFunction(
		[this, targetingpoint, cannonbarrel](float deltaTime, LambdaGameObject* self)
		{
			if (isCharge) {
				self->isVisible = true;
				targetingpoint->transform.position = lineCalc(power, cannonbarrel->transform.rotation.z);
				this->meshes["lines"].Load(0, line.data(), sizeof(float), 4, line.size());
			}
			else {
				self->isVisible = false;
			}
		}
	);
	this->opaqueObjects.emplace_back(lineObject);
	this->objects.emplace_back(lineObject);
	targetingpoint->AddSibiling(lineObject);


#pragma endregion


	skyBox->GetRenderItem().drawType = GL_TRIANGLES;
	skyBox->GetRenderItem().isLocalTwoSide = true;
	
	this->opaqueObjects.emplace_back(skyBox);
	this->objects.emplace_back(skyBox);
	this->parent->AddChild(skyBox);


	this->PlaySound("bgm");


}