#include <SettingState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <LevelManager.hpp>


SettingState::SettingState(StateStack& stack, Context context) : State(stack, context) {
    mTextName.setFont(context.fonts->get(Fonts::Main));
    mTextName.setString("Setting");
    mTextName.setCharacterSize(30);
    mTextName.setFillColor(sf::Color(0, 0, 0, 255));
    mTextName.setOrigin(mTextName.getLocalBounds().width / 2.0f, mTextName.getLocalBounds().height / 2.0f);
    mTextName.setPosition(640, 230);

    SoundButton.setTexture(context.textures->get(Textures::SettingSoundButton));
    SoundButton.setPosition(530, 284);

    MusicButton.setTexture(context.textures->get(Textures::SettingMusicButton));
    MusicButton.setPosition(530, 355);

    mTextSound.setFont(context.fonts->get(Fonts::Main));
    mTextSound.setString("Sound: ON");
    mTextSound.setCharacterSize(20);
    mTextSound.setFillColor(sf::Color(0, 0, 0, 255));
    mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
    mTextSound.setPosition(640, 305);

    mTextMusic.setFont(context.fonts->get(Fonts::Main));
    mTextMusic.setString("Music: ON");
    mTextMusic.setCharacterSize(20);
    mTextMusic.setFillColor(sf::Color(0, 0, 0, 255));
    mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
    mTextMusic.setPosition(640, 375);

    mBackgroundSprite.setTexture(context.textures->get(Textures::SettingBoard));
    mBackgroundSprite.setOrigin(mBackgroundSprite.getLocalBounds().width / 2.0f, mBackgroundSprite.getLocalBounds().height / 2.0f);
    mBackgroundSprite.setPosition(640, 320);

    CloseButton.setTexture(context.textures->get(Textures::SettingCloseButton));
    CloseButton.setPosition(750, 405);


}

void SettingState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 128));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));
    backgroundShape.setPosition(0, 0);

    window.draw(backgroundShape);

    window.draw(mBackgroundSprite);
    window.draw(mTextName);
    window.draw(SoundButton);
    window.draw(MusicButton);
    window.draw(mTextSound);
    window.draw(mTextMusic);
    window.draw(CloseButton);



}

bool SettingState::update(sf::Time deltatime)
{
    return false;
}

bool SettingState::handleEvent(const sf::Event& event)
{

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (SoundButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                if (cnt_sound % 2 == 0) {
                    mTextSound.setString("Sound: OFF");
                    mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
                    mTextSound.setPosition(640, 305);
                }
                else {
                    mTextSound.setString("Sound: ON");
                    mTextSound.setOrigin(mTextSound.getLocalBounds().width / 2.0f, mTextSound.getLocalBounds().height / 2.0f);
                    mTextSound.setPosition(640, 305);
                }
                cnt_sound++;
            }
            else if (MusicButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                if (cnt_music % 2 == 0) {
                    mTextMusic.setString("Music: OFF");
                    mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
                    mTextMusic.setPosition(640, 375);
                }
                else {
                    mTextMusic.setString("Music: ON");
                    mTextMusic.setOrigin(mTextMusic.getLocalBounds().width / 2.0f, mTextMusic.getLocalBounds().height / 2.0f);
                    mTextMusic.setPosition(640, 375);
                }
                cnt_music++;
            }
            else if (CloseButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            requestStackPop();
        }
    }
    return false;
}