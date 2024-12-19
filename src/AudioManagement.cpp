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
	coinSound.setBuffer(coinSoundBuffer);
	jumpSound.setBuffer(jumpSoundBuffer);
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