#include "pch.h"
#include "Utill.h"
#include "framework.h"
#include "GameObject.h"
#include "LambdaGameObject.h"
#include "Timer.h"
#include "Color.h"


std::unique_ptr<Framework> Framework::instance = nullptr;

void Framework::Start(int argc, char** argv)
{
	FreeImage_Initialise(TRUE);
	this->width = 1280;
	this->height = 720;
	this->aspect = float(this->width) / float(this->height);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(this->width, this->height);
	glutCreateWindow("The Cannon");

	// ��� Ȱ��ȭ
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	// GLEW�ʱ�ȭ
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to Initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW Initialized" << std::endl;
	}
	glutDisplayFunc([]() {Framework::GetInstance()->Draw(); });

	glutSpecialFunc(
		[](int key, int x, int y)
		{
			Framework::GetInstance()->SpecialInput(key, x, y);
		}
	);
	glutSpecialUpFunc(
		[](int key, int x, int y)
		{
			Framework::GetInstance()->SpecialUpInput(key, x, y);
		}
	);

	glutReshapeFunc(
		[](int x, int y)
		{
			Framework::GetInstance()->Reshape(x, y);
		}
	);

	glutKeyboardFunc(
		[](unsigned char c, int x, int y)
		{
			Framework::GetInstance()->KeyInput(c, x, y);
		}
	);
	glutKeyboardUpFunc(
		[](unsigned char c, int x, int y)
		{
			Framework::GetInstance()->KeyUpInput(c, x, y);
		}
	);

	glutMouseFunc(
		[](int button, int state, int x, int y)
		{
			Framework::GetInstance()->MouseInput(button, state, x, y);
		}
	);
	glutMotionFunc(
		[](int x, int y)
		{
			Framework::GetInstance()->MotionInput(x, y);
		}
	);
	glutPassiveMotionFunc(
		[](int x, int y)
		{
			Framework::GetInstance()->PassiveMotionInput(x, y);
		}
	);
	glutIdleFunc(
		[]()-> void
		{
			Framework::GetInstance()->Update();
		}
	);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	this->InitSoundSystem();
	this->BuildSounds();
	this->BuildShaders();
	this->BuildTexture();
	this->BuildMaterials();
	this->SetDefaultTexture();
	this->BuildVertexs();
	this->BuildGameObjects();
	this->BuildUiObjects();
	this->gameTimer.Reset();
	this->gameTimer.Start();
	glutMainLoop();
}

void Framework::Update()
{
	this->soundSystem->update();
	this->gameTimer.Tick();
	this->parent->UpdateTransform(glm::mat4(1.0f));
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(this->gameTimer.DeltaTime());
	}

	this->constant.viewTransform = this->currentCamera->GetViewMatrix();
	this->constant.projTransform = this->currentCamera->GetProjMatrix();
	this->constant.eyePosition = this->currentCamera->transform.currentTransform * glm::vec4(0.0f,0.0f,0.0f, 1.0f);
	this->minimapConstant.viewTransform = this->minimapCamera->GetViewMatrix();
	this->minimapConstant.projTransform = this->minimapCamera->GetProjMatrix();
	this->minimapConstant.eyePosition = this->minimapCamera->transform.currentTransform
		* glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);


	for (auto& light : this->lightObjects)
	{
		light.second->PostLight(constant);
		light.second->PostLight(minimapConstant);
	}

	this->CheckCollision();
	//UI PASS
	this->uiParent->UpdateTransform(glm::mat4(1.0f));
	for (size_t i = 0; i < uiObjects.size(); i++)
	{
		uiObjects[i]->Update(this->gameTimer.DeltaTime());
	}

	this->CheckDestroy();

	glutPostRedisplay();
}

void Framework::ChangeCamera(const std::string& tag)
{
	this->currentCamera = this->cameraObjects[tag];
}

void Framework::ChangeMinimapCamera(const std::string& tag)
{
	this->minimapCamera = this->cameraObjects[tag];
}

void Framework::Draw()
{
	this->SetViewport(0, 0, this->width, this->height);
	glClearColor(Color::Black.r, Color::Black.g, Color::Black.b, Color::Black.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(this->currentShaderProgram);





	this->nowConstant = &this->constant;
	this->constant.PostUniform(this->currentShaderProgram);
	for (auto& obj : this->opaqueObjects)
	{
		obj->Draw();
	}

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto& obj : this->transparentObjects)
	{
		obj->Draw();
	}


	if (this->isRenderCollision)
	{
		for (auto& obj : this->collisionObjects)
		{
			obj->Draw();
		}
	}
	glDisable(GL_BLEND);


	if (this->isDrawUI)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma region UI
		// UI
		this->SetViewport(0, 0, this->width, this->height);

		glClear(GL_DEPTH_BUFFER_BIT);

		glUseProgram(this->shaderPrograms.at("ui_def"));
		this->uiConstant.PostUniform(this->shaderPrograms.at("ui_def"));
		for (auto& obj : this->uiObjects)
		{
			obj->Draw();
		}
		glDisable(GL_BLEND);
		//UI
#pragma endregion

#pragma region MINIMAP

	/* 미니맵 */
		if (this->isMinimapEnable)
		{

			this->SetViewport(this->minimapPosition.x, this->minimapPosition.y, this->minimapSize.x, this->minimapSize.y);
			this->nowConstant = &this->minimapConstant;
			this->minimapConstant.PostUniform(this->currentShaderProgram);
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);
			for (auto& obj : this->opaqueObjects)
			{
				obj->Draw();
			}
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			for (auto& obj : this->transparentObjects)
			{
				obj->Draw();
			}

			if (this->isRenderCollision)
			{
				for (auto& obj : this->collisionObjects)
				{
					obj->Draw();
				}
			}
			glDisable(GL_BLEND);
		}
		/* 미니맵 */
#pragma endregion




		glDisable(GL_BLEND);
	}

	glutSwapBuffers();
}

void Framework::End()
{
	this->gameTimer.Start();
}

void Framework::CheckCollision()
{
	for (size_t i = 0; i < this->collisionObjects.size(); i++)
	{
		for (size_t k = i + 1; k < this->collisionObjects.size(); k++)
		{
			this->collisionObjects[i]->HandleCollision(
				*this->collisionObjects[k]
			);
		}
	}
}

void Framework::CheckDestroy()
{
	for (auto i = this->objects.begin(); i != this->objects.end(); i++)
	{
		if ((*i)->isDestroyed)
		{
			if (!(*i)->isEraseSubNode)
			{
				(*i)->GetParent()->DeleteChild(i->get());
			}
		}
	}

	for (auto i = this->opaqueObjects.begin(); i != this->opaqueObjects.end(); i++)
	{
		if ((*i)->isDestroyed)
		{
			i = opaqueObjects.erase(i);
			if (i == this->opaqueObjects.end())
			{
				break;
			}
		}
	}

	for (auto i = this->transparentObjects.begin(); i != this->transparentObjects.end(); i++)
	{
		if ((*i)->isDestroyed)
		{
			i = transparentObjects.erase(i);
			if (i == this->transparentObjects.end())
			{
				break;
			}
		}
	}
	for (auto i = this->collisionObjects.begin(); i != this->collisionObjects.end(); i++)
	{
		if ((*i)->isDestroyed)
		{
			i = collisionObjects.erase(i);
			if (i == this->collisionObjects.end())
			{
				break;
			}
		}
	}

	for (auto i = this->objects.begin(); i != this->objects.end(); i++)
	{
		if ((*i)->isDestroyed)
		{
			i = objects.erase(i);
			if (i == this->objects.end())
			{
				break;
			}
		}
	}
}

void Framework::ChangeGlobalWireFrame()
{
	for (auto& i : this->objects)
	{
		if (i->hasRenderItem())
		{
			i->GetRenderItem().isGlobalWireFramed = this->isWireFrame;
		}
	}
}

void Framework::ChangePrintUIBound()
{
	for (auto& i : this->uiObjects)
	{
		i->GetRenderItem().isGlobalWireFramed = this->isUIBoundFrame;
	}
}

void Framework::ChangeGlobalCullFace()
{
	for (auto& i : this->objects)
	{
		if (i->hasRenderItem())
		{
			i->GetRenderItem().isGlobalTwoSide = this->isCullFace;
		}
	}
}

void Framework::ChangeDebugCollision()
{
	for (auto* ptr : this->collisionObjects)
	{
		ptr->isVisible = isRenderCollision;
	}
}

void Framework::SetViewport(int x, int y, int w, int h) const
{
	static int _x = 0;
	static int _y = 0;
	static int _w = 0;
	static int _h = 0;
	if (_x != x || _y != y || _w != w || _h != h)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		glViewport(x, y, w, h);
	}
}

void Framework::Reshape(int x, int y)
{
	this->minimapPosition.x = this->minimapPosition.x * (static_cast<float>(x) / static_cast<float>(this->width));
	this->minimapPosition.y = this->minimapPosition.y * (static_cast<float>(y) / static_cast<float>(this->height));
	this->minimapSize.x = this->minimapSize.x * (static_cast<float>(x) / static_cast<float>(this->width));
	this->minimapSize.y = this->minimapSize.y * (static_cast<float>(y) / static_cast<float>(this->height));
	this->width = x;
	this->height = y;
}


void Framework::KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '/':
	{
		this->isWireFrame = !this->isWireFrame;
		this->ChangeGlobalWireFrame();
	}
	break;
	case '.':
	{
		this->isUIBoundFrame = !this->isUIBoundFrame;
		this->ChangePrintUIBound();
	}
	break;
	case ';':
	{
		this->isRenderCollision = !this->isRenderCollision;
		this->ChangeDebugCollision();
	}
	break;
	case 27:
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	for (auto& obj : this->objects)
	{
		obj->KeyHandler(key, x, y);
	}
	for (auto& obj : this->uiObjects)
	{
		obj->KeyHandler(key, x, y);
	}
}

void Framework::SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F12:
		glutFullScreenToggle();
		break;
	default:
		break;
	}

	for (auto& obj : this->objects)
	{
		obj->SpecialHandler(key, x, y);
	}
	for (auto& obj : this->uiObjects)
	{
		obj->SpecialHandler(key, x, y);
	}
}

void Framework::KeyUpInput(unsigned char key, int x, int y)
{
	for (auto& obj : this->objects)
	{
		obj->KeyUpHandler(key, x, y);
	}
	for (auto& obj : this->uiObjects)
	{
		obj->KeyUpHandler(key, x, y);
	}
}

void Framework::SpecialUpInput(int key, int x, int y)
{
	for (auto& obj : this->objects)
	{
		obj->SpecialUpHandler(key, x, y);
	}
	for (auto& obj : this->uiObjects)
	{
		obj->SpecialUpHandler(key, x, y);
	}
}

void Framework::MouseInput(int button, int state, int x, int y)
{
	float clipX = ((x / static_cast<float>(this->width) - 0.5f)) * 2;
	float clipY = ((1 - y / static_cast<float>(this->height)) - 0.5f) * 2;
	std::cout << "Clicked";
	fprintf(stdout, "X : %f , Y : %f \n", clipX, clipY);

	for (auto& obj : this->objects)
	{
		obj->MouseHandler(button, state, clipX, clipY);
	}
	for (auto& obj : this->uiObjects)
	{
		obj->MouseHandler(button, state, clipX, clipY);
	}
}

void Framework::MotionInput(int x, int y)
{
	float clipX = ((x / static_cast<float>(this->width) - 0.5f)) * 2;
	float clipY = ((1 - y / static_cast<float>(this->height)) - 0.5f) * 2;

	for (auto& obj : this->objects)
	{
		obj->MotionHandler(clipX, clipY);
	}
	for (auto& obj : this->uiObjects)
	{
		obj->MotionHandler(clipX, clipY);
	}
}

void Framework::PassiveMotionInput(int x, int y)
{
	float clipX = ((x / static_cast<float>(this->width) - 0.5f)) * 2;
	float clipY = ((1 - y / static_cast<float>(this->height)) - 0.5f) * 2;

	for (auto& obj : this->objects)
	{
		obj->PassiveMotionHandler(clipX, clipY);
	}
	for (auto& obj : this->uiObjects)
	{
		obj->PassiveMotionHandler(clipX, clipY);
	}
}

void Framework::ChangeShader(GLuint shaderProgram)
{
	if (shaderProgram != this->currentShaderProgram)
	{
		this->currentShaderProgram = shaderProgram;
		glUseProgram(this->currentShaderProgram);
		this->nowConstant->PostUniform(this->currentShaderProgram);
	}
}

void Framework::ChangeUIShader(GLuint shaderProgram)
{
	if (shaderProgram != this->currentShaderProgram)
	{
		this->currentShaderProgram = shaderProgram;
		glUseProgram(this->currentShaderProgram);
		this->uiConstant.PostUniform(this->currentShaderProgram);
	}
}

void Framework::TurnOnUI()
{
	this->isDrawUI = true;
}

void Framework::TurnOffUI()
{
	this->isDrawUI = false;
}
