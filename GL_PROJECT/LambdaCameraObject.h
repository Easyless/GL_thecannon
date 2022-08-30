#pragma once
#pragma once
#include <functional>
#include "GameObject.h"
#include "CameraObject.h"
class LambdaCameraObject : public CameraObject
{
public:
	using UpdateFunc = std::function<void(float, LambdaCameraObject*)>;
	using KeyFunc = std::function<void(unsigned char, float, float, LambdaCameraObject*)>;
	using KeyUpFunc = std::function<void(unsigned char, float, float, LambdaCameraObject*)>;
	using SpecialFunc = std::function<void(int, float, float, LambdaCameraObject*)>;
	using SpecialUpFunc = std::function<void(int, float, float, LambdaCameraObject*)>;
	using MouseFunc = std::function<void(int, int, float, float, LambdaCameraObject*)>;
	using MouseMotionFunc = std::function<void(float, float, LambdaCameraObject*)>;
	using PassiveMotionFunc = std::function<void(float, float, LambdaCameraObject*)>;
private:
	UpdateFunc updateFunction = nullptr;
	KeyFunc keyFunction = nullptr;
	KeyUpFunc keyUpFunction = nullptr;
	SpecialFunc specialFunction = nullptr;
	SpecialUpFunc specialUpFunction = nullptr;
	MouseFunc mouseFunction = nullptr;
	MouseMotionFunc motionFunction = nullptr;
	PassiveMotionFunc passiveMotionFunction = nullptr;
public:
	LambdaCameraObject(Framework* framework, GLuint shaderProgram = -1, const std::string& meshTag = "", const std::string& materialTag = "default");
	void PostUpdateFunction(UpdateFunc func);
	void PostKeyFunction(KeyFunc func);
	void PostKeyUpFunction(KeyUpFunc func);
	void PostSpecialFunction(SpecialFunc func);
	void PostSpecialUpFunction(SpecialUpFunc func);
	void PostMouseFunction(MouseFunc func);
	void PostMouseMotionFunction(MouseMotionFunc func);
	void PostPassiveMotionFunction(PassiveMotionFunc func);
	void Update(float deltaTime) override;
	void KeyHandler(unsigned char key, float x, float y) override;
	void SpecialHandler(int key, float x, float y) override;
	void KeyUpHandler(unsigned char key, float x, float y) override;
	void SpecialUpHandler(int key, float x, float y) override;
	void MouseHandler(int button, int state, float x, float y) override;
	void MotionHandler(float x, float y) override;
	void PassiveMotionHandler(float x, float y) override;

};
