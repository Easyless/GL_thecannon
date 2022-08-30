#include "pch.h"
#include "LambdaCameraObject.h"

LambdaCameraObject::LambdaCameraObject(Framework* framework, GLuint shaderProgram, const std::string& meshTag, const std::string& materialTag)
	: CameraObject(framework, shaderProgram, meshTag, materialTag)
{
}

void LambdaCameraObject::PostUpdateFunction(UpdateFunc func)
{
	this->updateFunction = func;
}

void LambdaCameraObject::PostKeyFunction(KeyFunc func)
{
	this->keyFunction = func;
}

void LambdaCameraObject::PostKeyUpFunction(KeyUpFunc func)
{
	this->keyUpFunction = func;
}

void LambdaCameraObject::PostSpecialFunction(SpecialFunc func)
{
	this->specialFunction = func;
}

void LambdaCameraObject::PostSpecialUpFunction(SpecialUpFunc func)
{
	this->specialUpFunction = func;
}

void LambdaCameraObject::PostMouseFunction(MouseFunc func)
{
	this->mouseFunction = func;
}

void LambdaCameraObject::PostMouseMotionFunction(MouseMotionFunc func)
{
	this->motionFunction = func;
}

void LambdaCameraObject::PostPassiveMotionFunction(PassiveMotionFunc func)
{
	this->passiveMotionFunction = func;
}


void LambdaCameraObject::Update(float deltaTime)
{
	if (this->updateFunction != nullptr && this->isActive)
	{
		this->updateFunction(deltaTime, this);
	}
}

void LambdaCameraObject::KeyHandler(unsigned char key, float x, float y)
{
	if (this->keyFunction != nullptr && this->isActive)
	{
		this->keyFunction(key, x, y, this);
	}
}

void LambdaCameraObject::SpecialHandler(int key, float x, float y)
{
	if (this->specialFunction != nullptr && this->isActive)
	{
		this->specialFunction(key, x, y, this);
	}
}

void LambdaCameraObject::KeyUpHandler(unsigned char key, float x, float y)
{
	if (this->keyUpFunction != nullptr && this->isActive)
	{
		this->keyUpFunction(key, x, y, this);
	}
}

void LambdaCameraObject::SpecialUpHandler(int key, float x, float y)
{
	if (this->specialUpFunction != nullptr && this->isActive)
	{
		this->specialUpFunction(key, x, y, this);
	}
}

void LambdaCameraObject::MouseHandler(int button, int state, float x, float y)
{
	if (this->mouseFunction != nullptr && this->isActive)
	{
		this->mouseFunction(button, state, x, y, this);
	}
}

void LambdaCameraObject::MotionHandler(float x, float y)
{
	if (this->motionFunction != nullptr && this->isActive)
	{
		this->motionFunction(x, y, this);
	}
}

void LambdaCameraObject::PassiveMotionHandler(float x, float y)
{
	if (this->passiveMotionFunction != nullptr && this->isActive)
	{
		this->passiveMotionFunction(x, y, this);
	}
}
