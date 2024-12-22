#include <PauseState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>


PauseState::PauseState(StateStack& stack, Context context, Level level, Character_1 character) : State(stack, context), mLevel(level), mCharacter(character) {
    mTextLevel.setFont(context.fonts->get(Fonts::Main));
    mTextLevel.setString("Level " + toString(level + 1));
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
                if (mLevel == Level1) {
                    if (mCharacter == wukong) {
                        requestStackPush(States::TransitionLevel1_1);
                    }
                    else {
                        requestStackPush(States::TransitionLevel1_2);
                    }
                }
                else if (mLevel == Level2) {
                    if (mCharacter == wukong) {
                        requestStackPush(States::TransitionLevel2_1);
                    }
                    else {
                        requestStackPush(States::TransitionLevel2_2);
                    }
                }
                else if (mLevel == Level3) {
                    if (mCharacter == wukong) {
                        requestStackPush(States::TransitionLevel3_1);
                    }
                    else {
                        requestStackPush(States::TransitionLevel3_2);
                    }
                }
                else if (mLevel == Level4) {
                    if (mCharacter == wukong) {
                        requestStackPush(States::TransitionLevel4_1);
                    }
                    else {
                        requestStackPush(States::TransitionLevel4_2);
                    }
                }
                else if (mLevel == Level5) {
                    if (mCharacter == wukong) {
                        requestStackPush(States::TransitionLevel5_1);
                    }
                    else {
                        requestStackPush(States::TransitionLevel5_2);
                    }
                }
            }
            else if (MenuButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                //requestStateClear();
                requestStackPush(States::TransitionMenu);
            }
            else if (SaveButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                std::cout << "Save button pressed" << std::endl;
            }
            else if (SoundButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                cnt_sound++;
                if (cnt_sound % 2 == 0) {
                    mTextSound.setString("Sound: ON");
                    //mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
                    //mTextSound.setPosition(640, 243);
                }
                else {
                    mTextSound.setString("Sound: OFF");
                    //mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
                    //mTextSound.setPosition(640, 243);
                }
            }
            else if (MusicButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                cnt_music++;
                if (cnt_music % 2 == 0) {
                    mTextMusic.setString("Music: ON");
                    //mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
                    //mTextMusic.setPosition(640, 315);
                }
                else {
                    mTextMusic.setString("Music: OFF");
                    //mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
                    //mTextMusic.setPosition(640, 315);
                }
            }
        }
    }
    return false;
}