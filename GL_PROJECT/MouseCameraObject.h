#pragma once
#include "CameraObject.h"
class MouseCameraObject : public CameraObject
{
private:
	bool isMoveForward = false;
	bool isMoveBackward = false;
	bool isMoveLeft = false;
	bool isMoveRight = false;
	bool isMoveUp = false;
	bool isMoveDown = false;
	bool isClicked = false;
	bool isPressLeft = false;
	bool isPressRight = false;
	bool isPressUp = false;
	bool isPressDown = false;
	float prevX;
	float prevY;
	//CameraObject* camera;
public:
	float speed = 3.5f;
	float cameraSpeed = 50.0f;
	MouseCameraObject(Framework* framework, GLuint shaderProgram = -1, const std::string& meshTag = "", const std::string& materialTag = "default");

	void Update(float deltaTime) override;
	void KeyHandler(unsigned char key, float x, float y) override;
	void KeyUpHandler(unsigned char key, float x, float y) override;
	void SpecialHandler(int key, float x, float y) override;
	void SpecialUpHandler(int key, float x, float y) override;
	void MouseHandler(int button, int state, float x, float y) override;
	void MotionHandler(float x, float y) override;

	//CameraObject* GetCamera() const;
};