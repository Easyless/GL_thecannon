#include "pch.h"
#include "MouseCameraObject.h"
#include "framework.h"

MouseCameraObject::MouseCameraObject(Framework* framework, GLuint shaderProgram, const std::string& meshTag, const std::string& materialTag)
	:CameraObject(framework, shaderProgram, meshTag, materialTag)
{
	//this->camera = new CameraObject(framework);
	//this->AddChild(camera);
	//framework->objects.emplace_back(this->camera);
}

void MouseCameraObject::Update(float deltaTime)
{
	if (this->isMoveForward)
	{
		this->transform.position += -1.0f * this->transform.Forward() * speed * deltaTime;
	}
	if (this->isMoveBackward)
	{
		this->transform.position += -1.0f * this->transform.BackWard() * speed * deltaTime;
	}
	if (this->isMoveLeft)
	{
		this->transform.position += -1.0f * this->transform.Left() * speed * deltaTime;
	}
	if (this->isMoveRight)
	{
		this->transform.position += -1.0f * this->transform.Right() * speed * deltaTime;
	}
	if (this->isMoveUp)
	{
		this->transform.position += 1.0f * this->transform.Up() * speed * deltaTime;
	}
	if (this->isMoveDown)
	{
		this->transform.position += 1.0f * this->transform.Down() * speed * deltaTime;
	}


	if (this->isPressUp)
	{
		this->transform.Rotate(glm::rotate(glm::radians(cameraSpeed), this->transform.Left()));
	}
	if (this->isPressDown)
	{
		this->transform.Rotate(glm::rotate(glm::radians(-cameraSpeed), this->transform.Left()));
	}
	if (this->isPressLeft)
	{
		this->transform.Rotate(glm::rotate(glm::radians(cameraSpeed), this->transform.yAxis));
	}
	if (this->isPressRight)
	{
		this->transform.Rotate(glm::rotate(glm::radians(-cameraSpeed), this->transform.yAxis));
	}
}

void MouseCameraObject::KeyHandler(unsigned char key, float x, float y)
{
	switch (key)
	{
		case 'w': case 'W':
		{
			this->isMoveForward = true;
		}
		break;
		case 's': case 'S':
		{
			this->isMoveBackward = true;
		}
		break;
		case 'a': case 'A':
		{
			this->isMoveLeft = true;
		}
		break;
		case 'd': case 'D':
		{
			this->isMoveRight = true;
		}
		break;
		case 'q': case 'Q':
		{
			this->isMoveUp = true;
		}
		break;
		case 'e': case 'E':
		{
			this->isMoveDown = true;
		}
		break;
		default:
			break;
	}
}

void MouseCameraObject::KeyUpHandler(unsigned char key, float x, float y)
{
	switch (key)
	{
		case 'w': case 'W':
		{
			this->isMoveForward = false;
		}
		break;
		case 's': case 'S':
		{
			this->isMoveBackward = false;
		}
		break;
		case 'a': case 'A':
		{
			this->isMoveLeft = false;
		}
		break;
		case 'd': case 'D':
		{
			this->isMoveRight = false;
		}
		break;
		case 'q': case 'Q':
		{
			this->isMoveUp = false;
		}
		break;
		case 'e': case 'E':
		{
			this->isMoveDown = false;
		}
		break;
		default:
			break;
	}
}

void MouseCameraObject::SpecialHandler(int key, float x, float y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		this->isPressUp = true;
	}
	break;
	case GLUT_KEY_DOWN:
	{
		this->isPressDown = true;
	}
	break;
	case GLUT_KEY_LEFT:
	{
		this->isPressLeft = true;
	}
	break;
	case GLUT_KEY_RIGHT:
	{
		this->isPressRight = true;
	}
	break;
	default:
		break;
	}
}

void MouseCameraObject::SpecialUpHandler(int key, float x, float y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		this->isPressUp = false;
	}
	break;
	case GLUT_KEY_DOWN:
	{
		this->isPressDown = false;
	}
	break;
	case GLUT_KEY_LEFT:
	{
		this->isPressLeft = false;
	}
	break;
	case GLUT_KEY_RIGHT:
	{
		this->isPressRight = false;
	}
	break;
	default:
		break;
	}
}


void MouseCameraObject::MouseHandler(int button, int state, float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}

void MouseCameraObject::MotionHandler(float x, float y)
{
	this->transform.Rotate(glm::rotate(glm::radians((this->prevY - y) * cameraSpeed), this->transform.Right()));
	this->transform.Rotate(glm::rotate(glm::radians((this->prevX - x) * cameraSpeed), this->transform.yAxis));

	this->prevX = x;
	this->prevY = y;
}

//CameraObject* MouseCameraObject::GetCamera() const
//{
//	return this->camera;
//}
