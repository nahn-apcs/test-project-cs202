#ifndef LEVEL_STATE_HPP
#define LEVEL_STATE_HPP

#include <SFML/Graphics.hpp>

#include <State.hpp>
#include <Container.hpp>
#include <vector>
#include <SceneNode.hpp>
#include <Command.hpp>
#include <CommandQueue.hpp>
#include <array>

class LevelState : public State {

public:
    LevelState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

private:

    enum Layer {
        Background,
        Text,
        LayerCount,
    };
    SceneNode                               mSceneGraph;
    std::array<SceneNode*, LayerCount>      mSceneLayers;
    CommandQueue                            mCommandQueue;

    GUI::Container mGUIContainer;


    sf::Sprite mBackButton;

    std::vector<sf::Sprite> mLock;
    std::vector<sf::Sprite> mPointer;
};

#endif // LEVEL_STATE_HPP