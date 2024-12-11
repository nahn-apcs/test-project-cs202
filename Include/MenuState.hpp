#ifndef MENU_MENU_STATE_HPP
#define MENU_MENU_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>

class MenuState : public State {

public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:
    std::vector<sf::Sprite> mBackgroundSprite;
    GUI::Container mGUIContainer;

};

#endif // MENU_MENU_STATE_HPP