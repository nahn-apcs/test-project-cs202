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
	void loadAudioResources();
	void playMainMusic();
	void playCoinSound();
	void playJumpSound();

};