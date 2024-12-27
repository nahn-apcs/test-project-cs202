#include "DrawEngine.h"

void DrawEngine::displayGameInfo(sf::RenderWindow& window, float elapsedTime, Map* map, Character* charac) {
	// Display the game info
	sf::Text coinText;
	coinText.setFont(font);
	coinText.setString("Coins: " + std::to_string(map->getCoinsNumber()));
	coinText.setFillColor(sf::Color::Yellow);
	coinText.setCharacterSize(24);
	coinText.setFillColor(sf::Color::Yellow);
	coinText.setPosition(10, 10);
	

	
	int seconds = static_cast<int>(elapsedTime);
	sf::Text timeText;
	timeText.setFont(font);
	timeText.setString("Time: " + std::to_string(seconds) + "s");
	timeText.setCharacterSize(24);
	timeText.setFillColor(sf::Color::Yellow);
	timeText.setPosition(210, 10);

	sf::Text levelText;
	levelText.setFont(font);
	levelText.setString("Level: " + std::to_string(map->level));
	levelText.setCharacterSize(24);
	levelText.setFillColor(sf::Color::Yellow);
	levelText.setPosition(410, 10);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score: " + std::to_string(map->score));
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setPosition(610, 10);

	sf::Text lvText;
	lvText.setFont(font);
	lvText.setString("HP: " + std::to_string(charac->getLevel()));
	lvText.setCharacterSize(24);
	lvText.setFillColor(sf::Color::Yellow);
	lvText.setPosition(910, 10);

	if (map->level == 1) {
		coinText.setFillColor(sf::Color::Black);
		timeText.setFillColor(sf::Color::Black);
		levelText.setFillColor(sf::Color::Black);
		scoreText.setFillColor(sf::Color::Black);
		lvText.setFillColor(sf::Color::Black);
	}
	else if (map->level == 2) {
		coinText.setFillColor(sf::Color::Yellow);
		timeText.setFillColor(sf::Color::Yellow);
		levelText.setFillColor(sf::Color::Yellow);
		scoreText.setFillColor(sf::Color::Yellow);
		lvText.setFillColor(sf::Color::Yellow);
	}
	else if (map->level == 3) {
		coinText.setFillColor(sf::Color::Yellow);
		timeText.setFillColor(sf::Color::Yellow);
		levelText.setFillColor(sf::Color::Yellow);
		scoreText.setFillColor(sf::Color::Yellow);
		lvText.setFillColor(sf::Color::Yellow);
	}
	// Draw the text to the window
	window.setView(window.getDefaultView());
	window.draw(coinText);
	window.draw(timeText);
	window.draw(levelText);
	window.draw(scoreText);
	window.draw(lvText);
}

void DrawEngine::displayBossHealth(sf::RenderWindow& window, float elapsedTime, Map* map, Character* charac, Boss* b) {
	// Display the boss health
	sf::Text bossHealthText;
	bossHealthText.setFont(font);
	std::string bossHealth = "Boss HP: ";
	for (int i = 0; i < b->getHealth(); i++) {
		bossHealth += "|";
	}
	bossHealthText.setString(bossHealth);
	bossHealthText.setCharacterSize(24);
	bossHealthText.setFillColor(sf::Color::Red);
	//bossHealthText.setOrigin(bossHealthText.getLocalBounds().width / 2, bossHealthText.getLocalBounds().height / 2);
	bossHealthText.setPosition(1280/2-60, 60);

	sf::Text bossNameText;
	bossNameText.setFont(font);
	bossNameText.setString("King Minotaur");
	bossNameText.setCharacterSize(40);
	bossNameText.setFillColor(sf::Color::Red);
	bossNameText.setOrigin(bossNameText.getLocalBounds().width / 2, bossNameText.getLocalBounds().height / 2);
	bossNameText.setPosition(1280 / 2, 20);

	int seconds = static_cast<int>(elapsedTime);
	sf::Text timeText;
	timeText.setFont(font);
	timeText.setString("Time: " + std::to_string(seconds) + "s");
	timeText.setCharacterSize(18);
	timeText.setFillColor(sf::Color::Yellow);
	timeText.setPosition(10, 50);

	sf::Text lvText;
	lvText.setFont(font);
	lvText.setString("HP: " + std::to_string(charac->getLevel()));
	lvText.setCharacterSize(18);
	lvText.setFillColor(sf::Color::Yellow);
	lvText.setPosition(50, 10);

	// Draw the text to the window
	window.setView(window.getDefaultView());
	window.draw(bossHealthText);
	window.draw(bossNameText);
	window.draw(timeText);
	window.draw(lvText);
}