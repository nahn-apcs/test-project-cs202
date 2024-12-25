#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>
#include <SceneNode.hpp>
#include <Command.hpp>
#include <array>
#include <CommandQueue.hpp>

class MenuState : public State {

public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:

    enum Layer {
        Background,
        Cloud,
        GameName,
        LayerCount,
    };

    SceneNode							mSceneGraph;
    std::array<SceneNode*, 3>	mSceneLayers;
    CommandQueue						mCommandQueue;

    GUI::Container mGUIContainer;


};

#endif // MENU_STATE_HPP