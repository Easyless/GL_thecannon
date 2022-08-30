#include "pch.h"
#include "framework.h"
#include "UIObject.h"
#include "UINumber.h"

bool isCleard = false;

void Framework::BuildUiObjects()
{
	this->isMinimapEnable = true;
	this->minimapPosition = glm::vec2(46, 34);
	this->minimapSize *= 1.07f;

	auto pt = new UIObject(this);
	this->uiObjects.emplace_back(pt);
	this->uiParent = pt;



	{
		//auto test = new UIObject(this, "Resource/ui/WireFence.png", FIF_PNG);
		auto power_gauge_back = new UIObject(this, "Resource/ui/power-gauge-back.png", FIF_PNG);

		power_gauge_back->transform.Rotate(
			glm::rotate(glm::radians(45.0f), glm::vec3(0, 0, 1)) *
			glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0))
		);
		power_gauge_back->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.2f;
		power_gauge_back->transform.lastScale = glm::vec3(1.0f, 1.0f * aspect, 1.0f);
		power_gauge_back->transform.position.x += 0.25f;
		power_gauge_back->transform.position.y += -0.35f;
		this->uiObjects.emplace_back(power_gauge_back);
		this->uiParent->AddChild(power_gauge_back);

		auto power_gauge = new UIObject(this, "Resource/ui/power-gauge.png", FIF_PNG);
		power_gauge->OnUpdate.Add(
			[this](float deltaTime, UIObject* self)
			{
				constexpr float start = 0.0f;
				constexpr float power_max = 70.0f;
				constexpr float rotate_max = 90.0f;
				static float dir = -1.0f;
				static float rotate = start;

				rotate = this->uiBoard.GetVariable<float>("cannon_power");
				rotate = 1 - rotate / power_max;
				rotate *= rotate_max;
				self->GetRenderItem().textureTrasform =
					glm::translate(glm::vec3(0, 1.0f, 0.0f)) *
					glm::rotate(glm::radians(rotate), glm::vec3(0, 0, 1.0f)) *
					glm::translate(glm::vec3(0, -1.0f, 0.0f));

			}
		);
		this->uiObjects.emplace_back(power_gauge);
		power_gauge_back->AddChild(power_gauge);
	}
	{
		auto test = new UINumber(this, 2,
			{
				"Resource/ui/font/0.png",
				"Resource/ui/font/1.png",
				"Resource/ui/font/2.png",
				"Resource/ui/font/3.png",
				"Resource/ui/font/4.png",
				"Resource/ui/font/5.png",
				"Resource/ui/font/6.png",
				"Resource/ui/font/7.png",
				"Resource/ui/font/8.png",
				"Resource/ui/font/9.png"
			}
		, FIF_PNG);
		test->transform.rotation.x = 90.0f;
		test->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f * aspect) * 0.05f;
		test->transform.position.x += 0.15f;
		test->transform.position.y -= 0.35f;
		test->textColor = Color::White;
		test->OnUpdate.Add(
			[this](float deltaTime, UIObject* self) {
				static_cast<UINumber*>(self)->currentValue = this->uiBoard.GetVariable<int>("fire_count");
			}
		);
		test->isVisible = false;
		this->uiObjects.emplace_back(test);
		this->uiParent->AddChild(test);
	}

	{

		//auto test = new UIObject(this, "Resource/ui/WireFence.png", FIF_PNG);
		auto signParent = new UIObject(this, "Resource/ui/sign.png", FIF_PNG);

		signParent->transform.Rotate(
			glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0))
		);
		signParent->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.15f;
		signParent->transform.lastScale = glm::vec3(1.0f, 1.0f * aspect, 1.0f);
		signParent->transform.position.x += 0.8f;
		signParent->transform.position.y += 0.8f;
		this->uiObjects.emplace_back(signParent);
		this->uiParent->AddChild(signParent);


		auto signNumber = new UINumber(this, 1,
			{
				"Resource/ui/font_2/0.png",
				"Resource/ui/font_2/1.png",
				"Resource/ui/font_2/2.png",
				"Resource/ui/font_2/3.png",
				"Resource/ui/font_2/4.png",
				"Resource/ui/font_2/5.png",
				"Resource/ui/font_2/6.png",
				"Resource/ui/font_2/7.png",
				"Resource/ui/font_2/8.png",
				"Resource/ui/font_2/9.png"
			}
		, FIF_PNG);
		signNumber->transform.position.x = -0.7f;
		signNumber->transform.position.z = -0.05f;
		signNumber->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.365f;

		//signNumber->textColor = Color::Blue;
		signNumber->OnUpdate.Add(
			[this](float deltaTime, UIObject* self) {
				static_cast<UINumber*>(self)->currentValue = 
					this->uiBoard.GetVariable<int>("target_count");
				if (this->uiBoard.GetVariable<int>("target_count") == 0)
				{
					isCleard = true;
				}
			}
		);
		this->uiObjects.emplace_back(signNumber);
		signParent->AddChild(signNumber);
	}

	{
		auto signParent = new UIObject(this, "Resource/texture/WoodCrate02.dds", FIF_DDS);

		signParent->transform.Rotate(
			glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0))
		);
		signParent->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 0.33f;
		signParent->transform.lastScale = glm::vec3(1.0f, 1.0f, 1.0f);
		signParent->transform.position.x -= 0.63f;
		signParent->transform.position.y -= 0.61f;
		this->uiObjects.emplace_back(signParent);
		this->uiParent->AddChild(signParent);
	}


	{
		auto Cleared = new UIObject(this, "Resource/ui/Cleared.png", FIF_PNG);

		Cleared->transform.Rotate(
			glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0))
		);
		Cleared->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
		Cleared->transform.lastScale = glm::vec3(1.0f, 1.0f * aspect, 1.0f);
		Cleared->GetRenderItem().objectColor.variable.a = 0.0f;
		Cleared->OnUpdate.Add(
			[this](float deltaTime, UIObject* self)
			{
				static float timer = 8.0f;
				static bool playSound = false;
				if (isCleard)
				{
					if ((timer < 5.0f) && !playSound)
					{
						this->PlaySound("clear");
						playSound = true;
					}
					timer -= deltaTime;
					this->isMinimapEnable = false;
					if (timer > 3.0f)
					{
						self->GetRenderItem().objectColor.variable.a = soy_clamp(1.0f - ((timer - 3.0f)/2.0f),	0.0f, 1.0f);
					}
					if (timer < 2.0f)
					{
						self->GetRenderItem().objectColor.variable.a = soy_clamp(timer-1.0f,0.0f,1.0f);
					}
					if (timer < 0)
					{
						self->isVisible = false;
						this->isMinimapEnable = true;
					}
				}
			}
		);
		this->uiObjects.emplace_back(Cleared);
		this->uiParent->AddChild(Cleared);
	}

	{
		auto title = new UIObject(this, "Resource/ui/title.png", FIF_PNG);

		title->transform.Rotate(
			glm::rotate(glm::radians(90.0f), glm::vec3(1, 0, 0))
		);
		title->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f) * 1.0f;
		title->transform.lastScale = glm::vec3(1.0f, 1.0f * aspect, 1.0f);
		title->GetRenderItem().objectColor.variable.a = 1.0f;
		title->OnUpdate.Add(
			[this](float deltaTime, UIObject* self)
			{
				static float timer = 4.0f;
				timer -= deltaTime;
				
				if (self->isVisible)
				{
					this->isMinimapEnable = false;
				}
				if (timer < 2.0f)
				{
					self->GetRenderItem().objectColor.variable.a = soy_clamp(timer - 1.0f, 0.0f, 1.0f);
				}
				if (timer < 0)
				{
					if (self->isVisible)
					{
						this->isMinimapEnable = true;
					}
					self->isVisible = false;
				}
			}
		);
		this->uiObjects.emplace_back(title);
		this->uiParent->AddChild(title);
	}


}