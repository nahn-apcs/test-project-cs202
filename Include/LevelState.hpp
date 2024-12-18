#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class LevelState : public State {

public:
    LevelState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:

    std::vector<sf::Sprite> mBackgroundSprite;
    sf::Text LevelText;
    GUI::Container mGUIContainer;
    sf::Sprite mBackButton;
    float elapsedTime = 0.f;
};

#endif // LEVEL_STATE_HPP