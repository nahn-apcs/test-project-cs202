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
    virtual void update(float deltaTime, Map* map);
    void move(float dx, float dy, Map* map);
    void pushBack(Map*);
    void dead(Map*);
    void jump();
    void shoot(Map* map);
    virtual void draw(sf::RenderWindow& window);
    void setVelocityX(float vx) { velocityX = vx; }
    void setVelocityY(float vy) { velocityY = vy; }
    virtual void drawBounds(sf::RenderWindow& window);
    void interact(float d, Map* map);
    void increaseSpeed();
    void levelUp(Map* map);
    void damaged(Map* map);
    bool isAttacking() const { return attacking; }
    bool isDead() const { return Dead; }
    void knockUp();
    int getLevel() const { return level; }
    sf::FloatRect getBounds() const;
    bool isEvoled() const { return status == 1; }
    sf::Vector2f getPosition() const { return sprite.getPosition(); }
    void setPosition(float x, float y) { sprite.setPosition(x, y); }
    float getVelocityX() const { return velocityX; }
    float getVelocityY() const { return velocityY; }
    int getHP() const { return level; }
    int getStatus() const { return status; }
    sf::Vector2f getVelocity() const { return sf::Vector2f(velocityX, velocityY); }



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
    virtual int checkWallCollision(float dx, float dy, Map* map);
};

class SecondCharacter : public Character {
public:
    SecondCharacter(std::vector<sf::Texture>& idleTextures, std::vector<sf::Texture>& runTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& jumpT, std::vector<sf::Texture>& hurt, std::vector<sf::Texture>& sidleTextures, std::vector<sf::Texture>& srunTextures, std::vector<sf::Texture>& sattackTextures, std::vector<sf::Texture>& sjumpT, std::vector<sf::Texture>& sHurt, std::vector<sf::Texture>& dead
        , int x, int y, int type);
    void interact(float d, Map* map);
};


class FirstCharacter : public Character {
public:
	FirstCharacter(std::vector<sf::Texture>& idleTextures, std::vector<sf::Texture>& runTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& jumpT, std::vector<sf::Texture>& hurt, std::vector<sf::Texture>& sidleTextures, std::vector<sf::Texture>& srunTextures, std::vector<sf::Texture>& sattackTextures, std::vector<sf::Texture>& sjumpT, std::vector<sf::Texture>& sHurt, std::vector<sf::Texture>& dead
		, int x, int y, int type) : Character(idleTextures, runTextures, attackTextures, jumpT, hurt, sidleTextures, srunTextures, sattackTextures, sjumpT, sHurt, dead, x, y, type) {}
};


class Boss : public Character {
public:
    Boss() = default;
    Boss(std::vector<sf::Texture>& flyTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& dieTextures, std::vector<sf::Texture>& exhaustTextures, std::vector<sf::Texture>& shootTextures, int x, int y);
    ~Boss();
    void update(float deltaTime, Map* map);
    void move(float dx, float dy, Map* map);
    void pushBack(Map*);
    void dead(Map*);
    void shoot(Map* map);
    void draw(sf::RenderWindow& window);
    void drawBounds(sf::RenderWindow& window);
    void interact(float d, Map* map, sf::Vector2f playerPos);
    void damaged(Map* map);
    sf::FloatRect getBounds() const;
    bool isAttacking() const { return attacking; }
    bool isDead() const { return Dead; }
    void activate() { activated = true; }
    void circularShoot(Map* map);
    void angularShoot(Map* map, sf::Vector2f playerPos);
    void normalAttack(Map* map);
    void rainShoot(Map* map);
    void shootFromFeet(Map* map);
    void groundShoot(Map* map);
    sf::Vector2f getPosition() const { return mPosition; }
    bool isActivated() const { return activated; }
    int getHP() const { return health; }
    sf::Vector2f getVelocity() const { return sf::Vector2f(velocityX, velocityY); }
private:
    Animation* flyAnimation;
    Animation* attackAnimation;
    Animation* dieAnimation;
    Animation* exhaustAnimation;
    Animation* shootAnimation;

    sf::Vector2f mPosition;
    bool mIsMovingRight;
    bool activated = false;
    bool shooting;
    bool isMoving = false;
    int hit = 0;
    bool exhaust = false;
    float exhaustTime = 0.f;
    int health = 50;
    int checkWallCollision(float dx, float dy, Map* map);
    float shootTime = 0.f;
    float moveTime = 0.f;
    float teleportTime = 0.f;
    float attackTime = 0.f;
};

#endif


