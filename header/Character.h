#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animation.h"

class Character {
public:
    Character() = default;
    Character(std::vector<sf::Texture>& idleTextures, std::vector<sf::Texture>& runTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& jumpT, std::vector<sf::Texture>& hurt, std::vector<sf::Texture>& sidleTextures, std::vector<sf::Texture>& srunTextures, std::vector<sf::Texture>& sattackTextures, std::vector<sf::Texture>& sjumpT, std::vector<sf::Texture>& sHurt, std::vector<sf::Texture>& dead
        , int x, int y, int type);
    ~Character();
    void update(float deltaTime, Map* map);
    void move(float dx, float dy, Map* map);
    void pushBack(Map*);
    void dead(Map*);
    void jump();
    void shoot(Map* map);
    void draw(sf::RenderWindow& window);
    void setVelocityX(float vx) { velocityX = vx; }
    void setVelocityY(float vy) { velocityY = vy; }
    void drawBounds(sf::RenderWindow& window);
    virtual void interact(float d, Map* map);
    void increaseSpeed();
    void levelUp(Map* map);
    void damaged(Map* map);
    bool isAttacking() const { return attacking; }
    bool isDead() const { return Dead; }
    void knockUp();
    int getLevel() const { return level; }
    sf::FloatRect getBounds() const;
    bool isEvoled() const { return status == 1; }

protected:
    sf::Sprite sprite;
    float velocityX, velocityY;
    bool onGround;
    bool isJumping;
    bool attacking;

    int status = 0;

    std::vector<Animation*> runAnimations;  // Vector of running animations
    std::vector<Animation*> attackAnimations;
    std::vector<Animation*> idleAnimations;
    std::vector<Animation*> jumpAnimations;
    std::vector<Animation*> hurtAnimations;
    Animation* deadAnimation;

    const float gravity = 600.f;
    float jumpStrength = -400.f;
    float moveSpeed = 100.f;
    float cooldown = 0.f;
    float dashCooldown = 0.f;
    bool faceRight;
    int level = 3;
    float unDamagedTime = 0.f;
    bool attacked = false;
    bool Dead = false;
    int type;
    void handleCollisions(Map* map);
    void applyGravity(float deltaTime);
    void applyFriction(float deltaTime);
    int checkWallCollision(float dx, float dy, Map* map);
};

class SecondCharacter : public Character {
public:
    SecondCharacter(std::vector<sf::Texture>& idleTextures, std::vector<sf::Texture>& runTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& jumpT, std::vector<sf::Texture>& hurt, std::vector<sf::Texture>& sidleTextures, std::vector<sf::Texture>& srunTextures, std::vector<sf::Texture>& sattackTextures, std::vector<sf::Texture>& sjumpT, std::vector<sf::Texture>& sHurt, std::vector<sf::Texture>& dead
        , int x, int y, int type);
    void interact(float d, Map* map);
};

#endif
