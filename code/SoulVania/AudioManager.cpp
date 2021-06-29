#include "stdafx.h"
#include "AudioManager.h"

AudioManager::SoundDict AudioManager::soundDict;
float AudioManager::volume;

void AudioManager::LoadContent(ContentManager& content)
{
	for (auto const& [audioName, path] : GAME_AUDIO)
	{
		soundDict[audioName] = content.Load<Sound>(path);
	}

	// Play sound the first time to 'load' it or the game will be lagged when the
	// first sound effects is actually played. TODO: hacky, need a proper fix
	Play(M_INTRO_SCENE);
	Stop(M_INTRO_SCENE);
}

void AudioManager::Play(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		PlaySound(*sound);
	}
}

void AudioManager::PlayOneInstance(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		if (!IsPlaying(name))
			PlaySound(*sound);
	}
}

void AudioManager::PlaySong(std::string name)
{
	PlayLoop(name);
}

void AudioManager::PlayLoop(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		PlaySound(*sound); // TODO: не зацикленно
	}
}
void AudioManager::Stop(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		StopSound(*sound);
	}
}

void AudioManager::StopAll()
{
	for (auto const& [name, sound] : soundDict)
	{
		if (sound != nullptr)
			StopSound(*sound);
	}
}

void AudioManager::Resume(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		ResumeSound(*sound);
	}
}

void AudioManager::Reset(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
	//	sound->Reset();
	}
}

bool AudioManager::IsPlaying(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		return IsSoundPlaying(*sound);
	}
	return false;
}