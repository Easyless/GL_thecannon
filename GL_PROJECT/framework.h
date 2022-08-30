#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>

#include <fmod/fmod.h>
#include <fmod/fmod.hpp>

#include "GL_HEADER.h"
#include "Singleton.h"
#include "Timer.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "LightObejct.h"
#include "Collision.h"
#include "Material.h"
#include "VertexArrayObject.h"
#include "ConstantVariable.h"
#include "Texture.h"
#include "UIObject.h"
#include "UIConstantVariable.h"

#include "BlackBoard.h"


class Framework : public Singleton<Framework>
{
private:
	GLuint currentShaderProgram = -1;
public:
	size_t width = 0;
	size_t height = 0;
	float aspect = 0.0f;
	bool isWireFrame = false;
	bool isUIBoundFrame = false;
	bool isCullFace = false;
	bool isRenderCollision = false;
	bool isDrawUI = true;
	Timer gameTimer = Timer();

	VertexArrayObject<2> UIPlane;

	std::map<std::string, GLuint> shaderPrograms;
	std::map<std::string, VertexArrayObject<4>> meshes;
	std::vector<std::unique_ptr<GameObject>> objects;
	std::vector<GameObject*> opaqueObjects;
	std::vector<GameObject*> transparentObjects;
	std::map<std::string, GameObject*> tagObjects;
	std::map<std::string, CameraObject*> cameraObjects;
	std::map<std::string, LightObject*> lightObjects;

	std::vector<CollisionBox*> collisionObjects;
	std::vector<std::unique_ptr<UIObject>> uiObjects;
	std::map<std::string, UIObject*> tagUiObjects;


	std::map<std::string, Material> materials;
	std::map<std::string, Texture> textures;

	std::map<std::string, FMOD::Sound*> sounds;
	FMOD::Channel* EffectChannel = nullptr;
	FMOD::Channel* BackgroundChannel = nullptr;
	FMOD::System* soundSystem = nullptr;

	void PlaySound(const std::string& tag, bool isBack = false);


	GameObject* parent = nullptr;
	UIObject* uiParent = nullptr;
	CameraObject* currentCamera = nullptr;

	ConstantVariable* nowConstant = nullptr;

	ConstantVariable constant;
	UIConstantVariable uiConstant;

	bool isMinimapEnable = true;
	ConstantVariable minimapConstant;
	CameraObject* minimapCamera = nullptr;
	glm::vec2 minimapPosition;
	glm::vec2 minimapSize = glm::vec2(177,100);

	BlackBoard uiBoard;

	virtual ~Framework()
	{
	}

	void InitSoundSystem();

	void BuildSounds();
	void BuildShaders();
	void BuildMaterials();
	void BuildVertexs();
	void BuildGameObjects();
	void BuildTexture();
	void BuildUiObjects();
	void BuildMapObjects();
	void SetDefaultTexture();

	void Start(int argc, char** argv);
	void Update();
	void ChangeCamera(const std::string& tag);
	void ChangeMinimapCamera(const std::string& tag);
	void Draw();
	void End();
	void CheckCollision();
	void CheckDestroy();

	void ChangeGlobalWireFrame();
	void ChangePrintUIBound();
	void ChangeGlobalCullFace();
	void ChangeDebugCollision();

	void SetViewport(int x, int y, int w, int h) const;
	void Reshape(int x, int y);
	void KeyInput(unsigned char key, int x, int y);
	void SpecialInput(int key, int x, int y);
	void KeyUpInput(unsigned char key, int x, int y);
	void SpecialUpInput(int key, int x, int y);
	void MouseInput(int button, int state, int x, int y);
	void MotionInput(int x, int y);
	void PassiveMotionInput(int x, int y);

	void ChangeShader(GLuint shaderProgram);
	void ChangeUIShader(GLuint shaderProgram);

	void TurnOnUI();
	void TurnOffUI();


};