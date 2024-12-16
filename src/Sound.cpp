#include "Sound.h"
#include <iostream>

Sound::Sound(){}

void Sound::playBackgroundMusic(std::string& filepath)
{
	if (!music.openFromFile(filepath))
	{
		std::cout << "Error: Could not load music file" << std::endl;
	}
	music.setLoop(true);
	music.play();
}