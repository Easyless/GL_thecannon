#pragma once
#include <functional>
#include "LightObejct.h"

class LambdaLightObject : public LightObject
{
public:
	using UpdateFunc = std::function<void(float, LambdaLightObject*)>;
	using KeyFunc = std::function<void(unsigned char, float, float, LambdaLightObject*)>;
	using KeyUpFunc = std::function<void(unsigned char, float, float, LambdaLightObject*)>;
	using SpecialFunc = std::function<void(int, float, float, LambdaLightObject*)>;
	using SpecialUpFunc = std::function<void(int, float, float, LambdaLightObject*)>;
	using MouseFunc = std::function<void(int, int, float, float, LambdaLightObject*)>;
	using MouseMotionFunc = std::function<void(float, float, LambdaLightObject*)>;
	using PassiveMotionFunc = std::function<void(float, float, LambdaLightObject*)>;
protected:
	UpdateFunc updateFunction = nullptr;
	KeyFunc keyFunction = nullptr;
	KeyUpFunc keyUpFunction = nullptr;
	SpecialFunc specialFunction = nullptr;
	SpecialUpFunc specialUpFunction = nullptr;
	MouseFunc mouseFunction = nullptr;
	MouseMotionFunc motionFunction = nullptr;
	PassiveMotionFunc passiveMotionFunction = nullptr;
public:
	LambdaLightObject(Framework* framework, GLuint shaderProgram = -1, const std::string& meshTag = "", const std::string& materialTag = "default");
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