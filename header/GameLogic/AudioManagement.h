#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class AudioManagement
{
private:
	sf::Music mainMusic;

	sf::SoundBuffer coinSoundBuffer;
	sf::SoundBuffer jumpSoundBuffer;
	sf::SoundBuffer destroyBlockSoundBuffer;
	sf::SoundBuffer monsterHitSoundBuffer;

	sf::Sound coinSound;
	sf::Sound jumpSound;
	sf::Sound destroyBlockSound;
	sf::Sound monsterHitSound;

	bool mOnSound = 1;
public:
	AudioManagement();
	AudioManagement(const AudioManagement&) = default;
	AudioManagement& operator=(const AudioManagement& other) = default;
	~AudioManagement() = default;

	void loadAudioResources();
	void playMainMusic();
	void playCoinSound();
	void playJumpSound();
	void playDestroyBlockSound();
	void playMonsterHitSound();

	void stopMainMusic();

	void switchOnOff();
	bool isOnSound() const;
};