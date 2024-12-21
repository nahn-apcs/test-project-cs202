#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class AudioManagement
{
private:
	sf::Music mainMusic;

	sf::SoundBuffer coinSoundBuffer;
	sf::SoundBuffer jumpSoundBuffer;

	sf::Sound coinSound;
	sf::Sound jumpSound;
public:
	AudioManagement();
	AudioManagement(const AudioManagement&) = default;
	AudioManagement& operator=(const AudioManagement& other) = default;
	~AudioManagement() = default;
	void loadAudioResources();
	void playMainMusic();
	void playCoinSound();
	void playJumpSound();

};