#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <ResourceID.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <StateStack.hpp>

class Application {

public:
                                Application();
    void                        run();

private:
    void                        processInput();
    void                        update(sf::Time dt);
    void                        render();

    void                        registerStates();

private:
    static const sf::Time       TimePerFrame;

    sf::RenderWindow            mWindow;
    TextureHolder               mTextures;
    FontHolder                  mFonts;
    StateStack                  mStateStack;

};


#endif // APPLICATION_HPP