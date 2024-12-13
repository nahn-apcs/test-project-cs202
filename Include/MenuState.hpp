#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

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

    enum TextState {
        ScalingUp,
        None,
    };

    std::vector<sf::Sprite> mBackgroundSprite;
    std::vector<sf::Sprite> mCloundSprite;
    GUI::Container mGUIContainer;

    sf::Text wukongText;
    sf::Text shadowText;
    float mScale = 0.1f;
    float mWukongAlpha = 255;
    bool mFadingOut = true;
    TextState mTextState = ScalingUp;

};

#endif // MENU_STATE_HPP