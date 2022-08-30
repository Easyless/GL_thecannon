#pragma once
#include <functional>
#include "GameObject.h"
class LambdaGameObject : public GameObject
{
public:
	using UpdateFunc = std::function<void(float, LambdaGameObject*)>;
	using KeyFunc = std::function<void(unsigned char, float, float, LambdaGameObject*)>;
	using KeyUpFunc = std::function<void(unsigned char, float, float, LambdaGameObject*)>;
	using SpecialFunc = std::function<void(int, float, float, LambdaGameObject*)>;
	using SpecialUpFunc = std::function<void(int, float, float, LambdaGameObject*)>;
	using MouseFunc = std::function<void(int, int, float, float, LambdaGameObject*)>;
	using MouseMotionFunc = std::function<void(float, float, LambdaGameObject*)>;
	using PassiveMotionFunc = std::function<void(float, float, LambdaGameObject*)>;
	using DrawFunc = std::function<void(LambdaGameObject*)>;
protected:
	UpdateFunc updateFunction = nullptr;
	KeyFunc keyFunction = nullptr;
	KeyUpFunc keyUpFunction = nullptr;
	SpecialFunc specialFunction = nullptr;
	SpecialUpFunc specialUpFunction = nullptr;
	MouseFunc mouseFunction = nullptr;
	MouseMotionFunc motionFunction = nullptr;
	PassiveMotionFunc passiveMotionFunction = nullptr;
	DrawFunc drawFunc = nullptr;
public:
	LambdaGameObject(Framework* framework, GLuint shaderProgram = -1, const std::string& meshTag = "", const std::string& materialTag = "default");
	void PostUpdateFunction(UpdateFunc func);
	void PostKeyFunction(KeyFunc func);
	void PostKeyUpFunction(KeyUpFunc func);
	void PostSpecialFunction(SpecialFunc func);
	void PostSpecialUpFunction(SpecialUpFunc func);
	void PostMouseFunction(MouseFunc func);
	void PostMouseMotionFunction(MouseMotionFunc func);
	void PostPassiveMotionFunction(PassiveMotionFunc func);
	void PostDrawFunction(DrawFunc func);

	void Draw() override;
	void Update(float deltaTime) override;
	void KeyHandler(unsigned char key, float x, float y) override;
	void SpecialHandler(int key, float x, float y) override;
	void KeyUpHandler(unsigned char key, float x, float y) override;
	void SpecialUpHandler(int key, float x, float y) override;
	void MouseHandler(int button, int state, float x, float y) override;
	void MotionHandler(float x, float y) override;
	void PassiveMotionHandler(float x, float y) override;
};
