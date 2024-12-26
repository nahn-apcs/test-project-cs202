#include <SFML/Audio.hpp>
#include <string>
class Sound {
private:
	sf::Music music;
public:
	Sound();
	void playBackgroundMusic(std::string& filePath);
};