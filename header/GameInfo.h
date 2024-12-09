#include <SFML/Graphics.hpp>

void displayGameInfo() {
	sf::Font font;
	font.loadFromFile("../resources/font/Arial.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(10, 10);
	text.setString("Score: 0");

	//display time by seconds
	sf::Clock clock;
	sf::Time time;
	sf::Text timeText;
	timeText.setFont(font);
	timeText.setCharacterSize(24);
	timeText.setFillColor(sf::Color::Blue);
	timeText.setPosition(10, 40);
	timeText.setString("Time: 0");
}