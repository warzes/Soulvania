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

	// Play sound the first time to 'load' it or the game will be lagged when the
	// first sound effects is actually played. TODO: hacky, need a proper fix
	//auto dummySound = soundDict.begin()->second;
	//if (dummySound != nullptr)
	//{
	//	dummySound->Play(0, 0, DSBVOLUME_MIN);
	//}
}

void TestAudioManager::Play(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
	//	sound->Play();
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
	//	sound->Play(0, DSBPLAY_LOOPING);
	}
}
void TestAudioManager::Stop(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
	//	sound->Stop();
	}
}

bool TestAudioManager::IsPlaying(std::string name)
{
	auto sound = soundDict[name];
	if (sound != nullptr)
	{
	//	return sound->IsSoundPlaying();
	}
	return false;
}