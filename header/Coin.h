#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include "CoinAnimation.h"

class Coin {
public:
    Coin(sf::Texture& texture, int x, int y);
    ~Coin();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isCollected() const;
    void collect(); // Mark coin as collected
    void update(float deltatime);

private:
    sf::Sprite sprite;
    bool collected;
    CoinAnimation* animation;
};



#endif // COIN_H
