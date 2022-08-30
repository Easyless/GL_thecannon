#pragma once
#include "IDrawable.h"
#include "IUpdatable.h"
#include "Hierarchy.h"
#include "Transform.h"
#include "RenderItem.h"

class Framework;

class GameObject : public IUpdatable, public IDrawable, public Hierarchy<GameObject>
{
protected:
	Framework* framework = nullptr;
	std::unique_ptr<RenderItem> renderItem = nullptr;
public:
	bool isDestroyed = false;
	bool isActive = true;
	bool isVisible = true;
	Transform transform;
	GameObject(Framework* framework, GLuint shaderProgram = -1, const std::string& meshTag = "", const std::string& materialTag = "default");
	RenderItem& GetRenderItem();
	virtual void UpdateTransform(glm::mat4 parentTransform);
	virtual void Update(float deltaTime) override;
	virtual void Draw();
	void Destory();
	bool hasRenderItem() const;

	// 콜백함수
	virtual void KeyHandler(unsigned char key, float x, float y);
	virtual void KeyUpHandler(unsigned char key, float x, float y);
	virtual void SpecialHandler(int key, float x, float y);
	virtual void SpecialUpHandler(int key, float x, float y);
	virtual void MouseHandler(int button, int state, float x, float y);
	virtual void MotionHandler(float x, float y);
	virtual void PassiveMotionHandler(float x, float y);
};