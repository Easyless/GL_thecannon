#pragma once
#include <memory>
#include <functional>
#include <map>
#include <type_traits>
#include <cassert>

#include "IUpdatable.h"
#include "IDrawable.h"
#include "Hierarchy.h"
#include "UIRenderItem.h"

#include "CallChain.h"
#include "BlackBoard.h"
#include "Transform.h"

class Framework;

class UIObject : public IUpdatable , public IDrawable, public Hierarchy<UIObject>
{
public:
	using UpdateFunc = std::function<void(float, UIObject*)>;
	using KeyFunc = std::function<void(unsigned char, float, float, UIObject*)>;
	using KeyUpFunc = std::function<void(unsigned char, float, float, UIObject*)>;
	using SpecialFunc = std::function<void(int, float, float, UIObject*)>;
	using SpecialUpFunc = std::function<void(int, float, float, UIObject*)>;
	using MouseFunc = std::function<void(int, int, float, float, UIObject*)>;
	using MouseMotionFunc = std::function<void(float, float, UIObject*)>;
	using PassiveMotionFunc = std::function<void(float, float, UIObject*)>;
protected:
	Framework* framework = nullptr;
	std::unique_ptr<UIRenderItem> renderItem = nullptr;
	bool isDestroyed = false;
public:
	bool isVisible = false;
	BlackBoard blackBoard;
	Transform transform;

	UIObject(Framework* framework, GLuint shaderProgram = 0);
	UIObject(Framework* framework, const std::string& dir, FREE_IMAGE_FORMAT format, GLuint shaderProgram = 0);

	UIRenderItem& GetRenderItem();

	virtual void UpdateTransform(glm::mat4 parentTransform);

	// 콜백함수
	virtual void Draw() override;
	virtual void Update(float deltaTime);
	virtual void KeyHandler(unsigned char key, float x, float y);
	virtual void KeyUpHandler(unsigned char key, float x, float y);
	virtual void SpecialHandler(int key, float x, float y);
	virtual void SpecialUpHandler(int key, float x, float y);
	virtual void MouseHandler(int button, int state, float x, float y);
	virtual void MotionHandler(float x, float y);
	virtual void PassiveMotionHandler(float x, float y);
	
	virtual bool CheckClicked(float x, float y) const;


	CallChain<UpdateFunc> OnUpdate;
	CallChain<KeyFunc> OnKeyDown;
	CallChain<KeyUpFunc> OnKeyUp;
	CallChain<SpecialFunc> OnSpecial;
	CallChain<SpecialUpFunc> OnSpecialUp;
	CallChain<MouseFunc> OnClick;
	CallChain<MouseMotionFunc> OnMotion;
	CallChain<PassiveMotionFunc> OnPassiveMotion;
};
