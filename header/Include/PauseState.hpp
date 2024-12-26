#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class PauseState : public State {

public:
    PauseState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    sf::Text mTextLevel;
    sf::Text mTextSound;
    sf::Text mTextMusic;
    sf::Sprite SoundButton;
    sf::Sprite MusicButton;

    sf::Sprite ContinueButton;
    sf::Sprite RestartButton;
    sf::Sprite MenuButton;
    sf::Sprite SaveButton;
    sf::Sprite PauseBG;

};

#endif // PAUSE_STATE_HPP