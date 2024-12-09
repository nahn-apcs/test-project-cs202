#include "DrawEngine.h"

void DrawEngine::displayGameInfo(sf::RenderWindow& window, sf::Clock& timeClock, Map& map) {
	// Display the game info
	sf::Text coinText;
	coinText.setFont(font);
	coinText.setString("Coins: " + std::to_string(map.coinCount));

	coinText.setCharacterSize(24);
	coinText.setFillColor(sf::Color::Black);
	coinText.setPosition(10, 10);
	

	// Display the time
	sf::Time elapsedTime = timeClock.getElapsedTime();
	int seconds = static_cast<int>(elapsedTime.asSeconds());
	sf::Text timeText;
	timeText.setFont(font);
	timeText.setString("Time: " + std::to_string(seconds) + "s");
	timeText.setCharacterSize(24);
	timeText.setFillColor(sf::Color::Black);
	timeText.setPosition(210, 10);

	sf::Text levelText;
	levelText.setFont(font);
	levelText.setString("Level: 1");
	levelText.setCharacterSize(24);
	levelText.setFillColor(sf::Color::Black);
	levelText.setPosition(410, 10);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(map.score));
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition(610, 10);
	// Draw the text to the window
	window.setView(window.getDefaultView());
	window.draw(coinText);
	window.draw(timeText);
	window.draw(levelText);
	window.draw(scoreText);
}