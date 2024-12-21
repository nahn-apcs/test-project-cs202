#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"
//sf::Font font;
//if (!font.loadFromFile("../resources/font/Pixel_NES.otf")) { // Replace with the correct font path
//    return -1; // Error loading font
//}
class DrawEngine {
private:
	sf::Font font;
public:
	DrawEngine() {
		font.loadFromFile("../resources/font/Pixel_NES.otf");
	}
	void displayGameInfo(sf::RenderWindow& window, sf::Clock& timeClock, Map* map, Character* charac);
};