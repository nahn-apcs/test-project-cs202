#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"

class Character {
public:
    Character(sf::Texture& texture, int x, int y);

    void update(float deltaTime, const Map& map);
    void move(float dx, float dy, const Map& map);
    void jump();
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    float velocityX, velocityY;
    bool onGround;
    bool isJumping;

    const float gravity = 400.f;
    const float jumpStrength = -600.f;
    const float moveSpeed = 200.f;

    void handleCollisions(const Map& map);
    void applyGravity(float deltaTime);
    int checkWallCollision(float dx, float dy, const Map& map);
};

#endif
