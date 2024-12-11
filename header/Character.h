#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"

class Character {
public:
    Character(sf::Texture& idleTexture, std::vector<sf::Texture>& runTextures, std::vector<sf::Texture>& aTextures, int x, int y);
    ~Character();
    void update(float deltaTime, const Map& map);
    void move(float dx, float dy, const Map& map);
    void jump();
    void shoot( Map& map);
    void draw(sf::RenderWindow& window);
    void setVelocityX(float vx) { velocityX = vx; }
    void setVelocityY(float vy) { velocityY = vy; }
    void drawBounds(sf::RenderWindow& window);
    void interact(float d,  Map& map);
    void increaseSpeed();
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
    float velocityX, velocityY;
    bool onGround;
    bool isJumping;
    bool attacking;
    Animation* runAnimation;  // Pointer to the running animation
    Animation* attackAnimation;
    sf::Texture idle;
    const float gravity = 600.f;
    const float jumpStrength = -400.f;
    float moveSpeed = 100.f;
    float cooldown = 0.f;
    bool faceRight;

    void handleCollisions(const Map& map);
    void applyGravity(float deltaTime);
    void applyFriction(float deltaTime);
    int checkWallCollision(float dx, float dy, const Map& map);
};

#endif
