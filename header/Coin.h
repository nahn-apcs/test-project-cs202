#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>

class Coin {
public:
    Coin(sf::Sprite& texture, int x, int y);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isCollected() const;
    void collect(); // Mark coin as collected

private:
    sf::Sprite sprite;
    bool collected;
};

#endif // COIN_H
