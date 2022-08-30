#include "pch.h"
#include "LambdaGameObject.h"

LambdaGameObject::LambdaGameObject(Framework* framework, GLuint shaderProgram, const std::string& meshTag, const std::string& materialTag)
	:GameObject(framework, shaderProgram, meshTag, materialTag)
{
}

void LambdaGameObject::PostUpdateFunction(UpdateFunc func)
{
	this->updateFunction = func;
}

void LambdaGameObject::PostKeyFunction(KeyFunc func)
{
	this->keyFunction = func;
}

void LambdaGameObject::PostKeyUpFunction(KeyUpFunc func)
{
	this->keyUpFunction = func;
}

void LambdaGameObject::PostSpecialFunction(SpecialFunc func)
{
	this->specialFunction = func;
}

void LambdaGameObject::PostSpecialUpFunction(SpecialUpFunc func)
{
	this->specialUpFunction = func;
}

void LambdaGameObject::PostMouseFunction(MouseFunc func)
{
	this->mouseFunction = func;
}

void LambdaGameObject::PostMouseMotionFunction(MouseMotionFunc func)
{
	this->motionFunction = func;
}

void LambdaGameObject::PostPassiveMotionFunction(PassiveMotionFunc func)
{
	this->passiveMotionFunction = func;
}

void LambdaGameObject::PostDrawFunction(DrawFunc func)
{
	this->drawFunc = func;
}

void LambdaGameObject::Draw()
{
	if (this->drawFunc != nullptr && this->isVisible)
	{
		this->drawFunc(this);
	}
	GameObject::Draw();
}

void LambdaGameObject::Update(float deltaTime)
{
	if (this->updateFunction != nullptr && this->isActive)
	{
		this->updateFunction(deltaTime, this);
	}
}

void LambdaGameObject::KeyHandler(unsigned char key, float x, float y)
{
	if (this->keyFunction != nullptr && this->isActive)
	{
		this->keyFunction(key, x, y, this);
	}
}

void LambdaGameObject::SpecialHandler(int key, float x, float y)
{
	if (this->specialFunction != nullptr && this->isActive)
	{
		this->specialFunction(key, x, y, this);
	}
}

void LambdaGameObject::KeyUpHandler(unsigned char key, float x, float y)
{
	if (this->keyUpFunction != nullptr && this->isActive)
	{
		this->keyUpFunction(key, x, y, this);
	}
}

void LambdaGameObject::SpecialUpHandler(int key, float x, float y)
{
	if (this->specialUpFunction != nullptr && this->isActive)
	{
		this->specialUpFunction(key, x, y, this);
	}
}

void LambdaGameObject::MouseHandler(int button, int state, float x, float y)
{
	if (this->mouseFunction != nullptr && this->isActive)
	{
		this->mouseFunction(button, state, x, y, this);
	}
}

void LambdaGameObject::MotionHandler(float x, float y)
{
	if (this->motionFunction != nullptr && this->isActive)
	{
		this->motionFunction(x, y, this);
	}
}

void LambdaGameObject::PassiveMotionHandler(float x, float y)
{
	if (this->passiveMotionFunction != nullptr && this->isActive)
	{
		this->passiveMotionFunction(x, y, this);
	}
}
