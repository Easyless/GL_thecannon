#include "pch.h"
#include "LambdaLightObject.h"

LambdaLightObject::LambdaLightObject(Framework* framework, GLuint shaderProgram, const std::string& meshTag, const std::string& materialTag)
	:LightObject(framework, shaderProgram, meshTag, materialTag)
{
}

void LambdaLightObject::PostUpdateFunction(UpdateFunc func)
{
	this->updateFunction = func;
}

void LambdaLightObject::PostKeyFunction(KeyFunc func)
{
	this->keyFunction = func;
}

void LambdaLightObject::PostKeyUpFunction(KeyUpFunc func)
{
	this->keyUpFunction = func;
}

void LambdaLightObject::PostSpecialFunction(SpecialFunc func)
{
	this->specialFunction = func;
}

void LambdaLightObject::PostSpecialUpFunction(SpecialUpFunc func)
{
	this->specialUpFunction = func;
}

void LambdaLightObject::PostMouseFunction(MouseFunc func)
{
	this->mouseFunction = func;
}

void LambdaLightObject::PostMouseMotionFunction(MouseMotionFunc func)
{
	this->motionFunction = func;
}

void LambdaLightObject::PostPassiveMotionFunction(PassiveMotionFunc func)
{
	this->passiveMotionFunction = func;
}


void LambdaLightObject::Update(float deltaTime)
{
	if (this->updateFunction != nullptr && this->isActive)
	{
		this->updateFunction(deltaTime, this);
	}
}

void LambdaLightObject::KeyHandler(unsigned char key, float x, float y)
{
	if (this->keyFunction != nullptr && this->isActive)
	{
		this->keyFunction(key, x, y, this);
	}
}

void LambdaLightObject::SpecialHandler(int key, float x, float y)
{
	if (this->specialFunction != nullptr && this->isActive)
	{
		this->specialFunction(key, x, y, this);
	}
}

void LambdaLightObject::KeyUpHandler(unsigned char key, float x, float y)
{
	if (this->keyUpFunction != nullptr && this->isActive)
	{
		this->keyUpFunction(key, x, y, this);
	}
}

void LambdaLightObject::SpecialUpHandler(int key, float x, float y)
{
	if (this->specialUpFunction != nullptr && this->isActive)
	{
		this->specialUpFunction(key, x, y, this);
	}
}

void LambdaLightObject::MouseHandler(int button, int state, float x, float y)
{
	if (this->mouseFunction != nullptr && this->isActive)
	{
		this->mouseFunction(button, state, x, y, this);
	}
}

void LambdaLightObject::MotionHandler(float x, float y)
{
	if (this->motionFunction != nullptr && this->isActive)
	{
		this->motionFunction(x, y, this);
	}
}

void LambdaLightObject::PassiveMotionHandler(float x, float y)
{
	if (this->passiveMotionFunction != nullptr && this->isActive)
	{
		this->passiveMotionFunction(x, y, this);
	}
}
