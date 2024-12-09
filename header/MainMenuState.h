#include "State.h"

class MainMenuState : public State {
public:
	MainMenuState();
	~MainMenuState();

	void handleInput(sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;

	void onEnter() override;
	void onExit() override;
};