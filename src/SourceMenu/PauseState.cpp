#include <PauseState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <LevelManager.hpp>
#include <fstream>

PauseState::PauseState(StateStack& stack, Context context) : State(stack, context) {
    mTextLevel.setFont(context.fonts->get(Fonts::Main));
    mTextLevel.setString("Level " + toString(LevelManager::getInstance().getCurLevel() + 1));
    mTextLevel.setCharacterSize(40);
    mTextLevel.setFillColor(sf::Color(0, 0, 0, 255));
    mTextLevel.setOrigin(mTextLevel.getLocalBounds().width / 2.0f, mTextLevel.getLocalBounds().height / 2.0f);
    mTextLevel.setPosition(640, 170);

    SoundButton.setTexture(context.textures->get(Textures::PauseSoundButton));
    SoundButton.setPosition(530, 225);

    MusicButton.setTexture(context.textures->get(Textures::PauseMusicButton));
    MusicButton.setPosition(530, 295);

    mTextSound.setFont(context.fonts->get(Fonts::Main));
    mTextSound.setString("Sound: ON");
    mTextSound.setCharacterSize(20);
    mTextSound.setFillColor(sf::Color(0, 0, 0, 255));
    mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
    mTextSound.setPosition(640, 243);

    mTextMusic.setFont(context.fonts->get(Fonts::Main));
    mTextMusic.setString("Music: ON");
    mTextMusic.setCharacterSize(20);
    mTextMusic.setFillColor(sf::Color(0, 0, 0, 255));
    mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
    mTextMusic.setPosition(640, 315);


    ContinueButton.setTexture(context.textures->get(Textures::PauseContinueButton));
    ContinueButton.setPosition(581, 383);

    RestartButton.setTexture(context.textures->get(Textures::PauseRestartButton));
    RestartButton.setPosition(657, 383);

    MenuButton.setTexture(context.textures->get(Textures::PauseMenuButton));
    MenuButton.setPosition(581, 446);

    SaveButton.setTexture(context.textures->get(Textures::PauseSaveButton));
    SaveButton.setPosition(657, 446);

    PauseBG.setTexture(context.textures->get(Textures::PauseBG));
    PauseBG.setPosition(340, 103);

	context.music->setPaused(1);
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 128));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    backgroundShape.setPosition(0, 0);

    window.draw(backgroundShape);

    window.draw(PauseBG);
    window.draw(mTextLevel);
    window.draw(SoundButton);
    window.draw(MusicButton);
    window.draw(mTextSound);
    window.draw(mTextMusic);
    window.draw(ContinueButton);
    window.draw(RestartButton);
    window.draw(MenuButton);
    window.draw(SaveButton);


}

bool PauseState::update(sf::Time deltatime)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (ContinueButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
                requestStackPush(States::Waiting);
            }
            else if (RestartButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
                requestStackPush(States::TransitionGame_2);
            }
            else if (MenuButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPush(States::TransitionMenu);
            }
            else if (SaveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Save button pressed" << std::endl;
                writeToFile();
            }
            else if (SoundButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                cnt_sound++;
                if (cnt_sound % 2 == 0) {
                    mTextSound.setString("Sound: ON");
                    mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
                    mTextSound.setPosition(640, 243);
                }
                else {
                    mTextSound.setString("Sound: OFF");
                    mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
                    mTextSound.setPosition(640, 243);
                }
            }
            else if (MusicButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                cnt_music++;
                if (cnt_music % 2 == 0) {
                    mTextMusic.setString("Music: ON");
                    mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
                    mTextMusic.setPosition(640, 315);
                }
                else {
                    mTextMusic.setString("Music: OFF");
                    mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
                    mTextMusic.setPosition(640, 315);
                }
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            requestStackPop();
            requestStackPush(States::Waiting);
        }
    }
    return false;
}

void PauseState::writeToFile() {
	std::ofstream file;
	file.open("../resources/save.txt");
	if (file.is_open()) {
		LevelManager& lm = LevelManager::getInstance();
        file << lm.getSaveLevel() << std::endl;
        file << lm.getSaveCharacter() << std::endl;
        file << lm.getSaveScore() << std::endl;
        file << lm.getSaveTime() << std::endl;

        file << lm.getSaveMap().size() << std::endl;
        for (int i = 0; i < lm.getSaveMap().size(); i++) {
			file << lm.getSaveMap()[i] << std::endl;
		}

        file << lm.getSaveMonsterPos().size() << std::endl;

        for (int i = 0; i < lm.getSaveMonsterPos().size(); i++) {
            file << lm.getSaveMonsterPos()[i].first << " " << lm.getSaveMonsterPos()[i].second << std::endl;
		}
        for (int i = 0; i < lm.getSaveMonsterType().size(); i++) {
			file << lm.getSaveMonsterType()[i] << std::endl;
        }

        file << lm.getSavePlayerProjectilePos().size() << std::endl;
        for (int i = 0; i < lm.getSavePlayerProjectilePos().size(); i++) {
			file << lm.getSavePlayerProjectilePos()[i].first << " " << lm.getSavePlayerProjectilePos()[i].second << std::endl;
		}
        for (int i = 0; i < lm.getSaveMonsterProjectilePos().size(); i++) {
            file << lm.getSaveMonsterProjectilePos()[i].first << " " << lm.getSaveMonsterProjectilePos()[i].second << std::endl;
            }
        for (int i = 0; i < lm.getSavePlayerProjectileDir().size(); i++) {
            file << lm.getSavePlayerProjectileDir()[i] << std::endl;
		}
        for (int i = 0; i < lm.getSaveMonsterProjectileDir().size(); i++) {
			file << lm.getSaveMonsterProjectileDir()[i] << std::endl;
            }
        for (int i = 0; i < lm.getSavePlayerProjectileVel().size(); i++) {
            file << lm.getSavePlayerProjectileVel()[i].first << " " << lm.getSavePlayerProjectileVel()[i].second << std::endl;
            }
        for (int i = 0; i < lm.getSaveMonsterProjectileVel().size(); i++) {
            file << lm.getSaveMonsterProjectileVel()[i].first << " " << lm.getSaveMonsterProjectileVel()[i].second << std::endl;
			}
        file << lm.getSaveItemPos().size() << std::endl;
        for (int i = 0; i < lm.getSaveItemPos().size(); i++) {
			file << lm.getSaveItemPos()[i].first << " " << lm.getSaveItemPos()[i].second << std::endl;
			}
        for (int i = 0; i < lm.getSaveItemType().size(); i++) {
			file << lm.getSaveItemType()[i] << std::endl;
            }
        file << lm.getSavePlayerPosX() << " " << lm.getSavePlayerPosY() << std::endl;
        file << lm.getPlayerHP() << std::endl;
        file << lm.getPlayerStatus() << std::endl;
        file << lm.getPlayerVelX() << " " << lm.getPlayerVelY() << std::endl;
        file << lm.getSaveBossPosX() << " " << lm.getSaveBossPosY() << std::endl;
        file << lm.getBossHP() << std::endl;
        file << lm.getBossVelX() << " " << lm.getBossVelY() << std::endl;


        //int score = 0;
        //int time = 0;
        //std::vector<std::string> saveMap;
        //std::vector<std::pair< float, float>> saveMonsterPos;
        //std::vector<char> saveMonsterType;

        ////projectile
        //std::vector<std::pair<float, float>> savePlayerProjectilePos;
        //std::vector<std::pair<float, float>> saveMonsterProjectilePos;
        //std::vector<bool> savePlayerProjectileDir;
        //std::vector<bool> saveMonsterProjectileDir;
        //std::vector<std::pair<float, float>> savePlayerProjectileVel;
        //std::vector<std::pair<float, float>> saveMonsterProjectileVel;

        ////item
        //std::vector<std::pair<float, float>> saveItemPos;
        //std::vector<int> saveItemType;
        ////coin = 1
        ////powerup = 2

        //float savePlayerPosX;
        //float savePlayerPosY;
        //int playerHP;
        //int playerStatus;
        //float playerVelX;
        //float playerVelY;

        ////boss
        //float saveBossPosX;
        //float saveBossPosY;
        //int bossHP;
        //float bossVelX;
        //float bossVelY;
	}

	file.close();
}