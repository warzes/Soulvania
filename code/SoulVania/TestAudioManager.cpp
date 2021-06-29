#include "stdafx.h"
#include "TestAudioManager.h"

std::map<std::string, std::shared_ptr<Sound>> TestAudioManager::soundDict;
float TestAudioManager::volume;

void TestAudioManager::LoadContent(ContentManager& content, std::vector<std::string> sounds)
{
	for (auto sound : sounds)
	{
		soundDict[sound] = content.Load<Sound>(sound + ".wav");
	}
}

void TestAudioManager::Play(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		PlaySound(*sound);
	}
}

void TestAudioManager::PlaySong(std::string name)
{
	PlayLoop(name);
}

void TestAudioManager::PlayLoop(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		PlaySound(*sound); // TODO: не зацикленно
	}
}
void TestAudioManager::Stop(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		StopSound(*sound);
	}
}

bool TestAudioManager::IsPlaying(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
		return IsSoundPlaying(*sound);
	}
	return false;
}