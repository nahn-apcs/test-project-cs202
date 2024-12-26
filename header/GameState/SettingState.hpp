#ifndef SETTING_STATE_HPP
#define SETTING_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class SettingState : public State {

public:
    SettingState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:

    sf::Sprite mBackgroundSprite;
    sf::RectangleShape mBackgroundShape;

    sf::Text mTextName;
    sf::Text mTextSound;
    int cnt_sound = 0;
    sf::Text mTextMusic;
    int cnt_music = 0;
    sf::Sprite SoundButton;
    sf::Sprite MusicButton;

    sf::Sprite CloseButton;

};

#endif // SETTING_STATE_HPP