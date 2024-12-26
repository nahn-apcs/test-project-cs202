#include <LevelCompleteState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <LevelManager.hpp>

LevelCompleteState::LevelCompleteState(StateStack& stack, Context context) : State(stack, context), mBackgroundSprite() {
    if (LevelManager::getInstance().getCurLevel() != LevelManager::Level5) {
        LevelManager::getInstance().setLevels(LevelManager::getInstance().getCurLevel() + 1, 1);
    }
    mBackgroundSprite.setTexture(context.textures->get(Textures::LevelCompleteBG));
    mBackgroundSprite.setPosition(300, 63);

    mBackButton.setTexture(context.textures->get(Textures::LevelCompleteBackButton));
    mBackButton.setPosition(512, 429);

    mNextButton.setTexture(context.textures->get(Textures::LevelCompleteNextButton));
    mNextButton.setPosition(628, 429);

	context.music->setVolume(70);
	context.music->play(Music::LevelCompleteTheme);
}

void LevelCompleteState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mBackgroundSprite);
    window.draw(mBackButton);
    window.draw(mNextButton);
    int mScore = LevelManager::getInstance().getScore();
    int mTime = LevelManager::getInstance().getTime();
    sf::Font& font = getContext().fonts->get(Fonts::PixelNes);
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: ");
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::Black);
    //scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);

    scoreText.setPosition(1280/2 - 40, 250);
    window.draw(scoreText);

    sf::Text scoreValue;
    scoreValue.setFont(font);
    scoreValue.setString(std::to_string(mScore));
    scoreValue.setCharacterSize(20);
    scoreValue.setFillColor(sf::Color::Black);
    scoreValue.setOrigin(scoreValue.getLocalBounds().width / 2, scoreValue.getLocalBounds().height / 2);

    scoreValue.setPosition(1280 / 2, 280);
    window.draw(scoreValue);

    sf::Text timeText;

    timeText.setFont(font);
    timeText.setString("Time: " + std::to_string(mTime) + "s");
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::Black);
    timeText.setOrigin(timeText.getLocalBounds().width / 2, timeText.getLocalBounds().height / 2);

    timeText.setPosition(1280 / 2, 320);
    window.draw(timeText);
}

bool LevelCompleteState::update(sf::Time deltatime) {
    return false;
}

bool LevelCompleteState::handleEvent(const sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (mBackButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
                requestStackPop();
            }
            else if (mNextButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
                if (LevelManager::getInstance().getCurLevel() == LevelManager::Level1) {
                    LevelManager::getInstance().setCurLevel(LevelManager::Level2);
                    requestStackPush(States::TransitionGame_2);
                }
                else if (LevelManager::getInstance().getCurLevel() == LevelManager::Level2) {
                    LevelManager::getInstance().setCurLevel(LevelManager::Level3);
                    requestStackPush(States::TransitionGame_2);
                }
                else if(LevelManager::getInstance().getCurLevel() == LevelManager::Level3) {
                    requestStackPush(States::TransitionWinning);
                }
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            requestStackPop();
            requestStackPop();
            this->getContext().music->play(Music::MenuTheme);
			this->getContext().music->setVolume(50);
        }
        else if (event.key.code == sf::Keyboard::Right) {
            requestStackPop();
            if (LevelManager::getInstance().getCurLevel() == LevelManager::Level1) {
                LevelManager::getInstance().setCurLevel(LevelManager::Level2);
                requestStackPush(States::TransitionGame_2);
            }
            else if (LevelManager::getInstance().getCurLevel() == LevelManager::Level2) {
                LevelManager::getInstance().setCurLevel(LevelManager::Level3);
                requestStackPush(States::TransitionGame_2);
            }
            else if (LevelManager::getInstance().getCurLevel() == LevelManager::Level3) {
                requestStackPush(States::TransitionWinning);
            }
        }
    }

    return false;
}
