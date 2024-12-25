#include "AudioManagement.h"

AudioManagement::AudioManagement()
{
	loadAudioResources();
}

void AudioManagement::loadAudioResources()
{
	if (!mainMusic.openFromFile("../resources/Audio/Background.wav"))
	{
		std::cout << "Error loading main music" << std::endl;
	}
	if (!coinSoundBuffer.loadFromFile("../resources/Audio/coin.wav"))
	{
		std::cout << "Error loading coin sound" << std::endl;
	}
	if (!jumpSoundBuffer.loadFromFile("../resources/Audio/jump.wav"))
	{
		std::cout << "Error loading jump sound" << std::endl;
	}
	if (!destroyBlockSoundBuffer.loadFromFile("../resources/Audio/rock-destroy.wav"))
	{
		std::cout << "Error loading destroy block sound" << std::endl;
	}
	if (!monsterHitSoundBuffer.loadFromFile("../resources/Audio/dead.wav"))
	{
		std::cout << "Error loading monster hit sound" << std::endl;
	}

	coinSound.setBuffer(coinSoundBuffer);
	jumpSound.setBuffer(jumpSoundBuffer);
	destroyBlockSound.setBuffer(destroyBlockSoundBuffer);
	monsterHitSound.setBuffer(monsterHitSoundBuffer);
}

void AudioManagement::playMainMusic()
{
	//set volume
	mainMusic.setVolume(20);
	mainMusic.setLoop(true);
	mainMusic.play();
}

void AudioManagement::playCoinSound()
{
	coinSound.play();
}

void AudioManagement::playJumpSound()
{
	jumpSound.play();
}

void AudioManagement::playDestroyBlockSound()
{
	destroyBlockSound.play();
}

void AudioManagement::stopMainMusic()
{
	mainMusic.stop();
}

void AudioManagement::playMonsterHitSound()
{
	monsterHitSound.setVolume(20);
	monsterHitSound.play();
}