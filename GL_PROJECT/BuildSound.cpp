#include "pch.h"
#include "framework.h"
#include "GL_HEADER.h"
#include "Utill.h"


#include <fmod/fmod.h>
#include <fmod/fmod.hpp>

void Framework::InitSoundSystem()
{
	FMOD::System_Create(&this->soundSystem);
	this->soundSystem->init(3, FMOD_INIT_NORMAL, NULL);
}

void Framework::BuildSounds()
{
	auto loadFunc = [this](const std::string& dir, bool isBgm = false)
	{
		FMOD::Sound* sound;
		if (isBgm)
		{
			this->soundSystem->createSound(dir.c_str(), FMOD_LOOP_NORMAL | FMOD_DEFAULT, NULL, &sound);
		}
		else 
		{
			this->soundSystem->createSound(dir.c_str(), FMOD_DEFAULT, NULL, &sound);
		}
		return sound;
	};
	this->sounds["bgm"] = loadFunc("Resource/sound/bgm.mp3", true);
	this->sounds["explosion"] = loadFunc("Resource/sound/explode2.wav", false);
	this->sounds["fire"] = loadFunc("Resource/sound/fire2.wav", false);
	this->sounds["clear"] = loadFunc("Resource/sound/vic1.wav", false);
}

void Framework::PlaySound(const std::string& tag, bool isBack)
{
	if (this->soundSystem != nullptr |this->sounds.count(tag) != 0)
	{
		this->soundSystem->playSound(
			this->sounds[tag],
			NULL,
			false,
			(isBack) ? (&this->BackgroundChannel) : (&this->EffectChannel)
		);
	}
}