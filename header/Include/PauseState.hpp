#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class PauseState : public State {

public:
    enum Level {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5
    };
    enum Character_1 {
        wukong,
        pig,
    };
    PauseState(StateStack& stack, Context context, Level level, Character_1 character);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Text mTextLevel;
    sf::Text mTextSound;
    int cnt_sound = 0;
    sf::Text mTextMusic;
    int cnt_music = 0;
    sf::Sprite SoundButton;
    sf::Sprite MusicButton;

    sf::Sprite ContinueButton;
    sf::Sprite RestartButton;
    sf::Sprite MenuButton;
    sf::Sprite SaveButton;
    sf::Sprite PauseBG;

    Level mLevel;
    Character_1 mCharacter;

};

#endif // PAUSE_STATE_HPP