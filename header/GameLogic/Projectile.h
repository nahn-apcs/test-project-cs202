#pragma once
#include <SFML/Graphics.hpp>
#include "ProjectileAnimation.h"

class Projectile {
	public:
	Projectile(sf::Texture& texture, float veloX, float veloY, float x, float y, bool mr);
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	bool isDestroyed() const;
    void destroy();
	sf::Vector2f getPosition() const { return sprite.getPosition();}
	bool getDirection() const { return moveRight; }
	sf::Vector2f getVelocity() const { return sf::Vector2f(veloX, veloY); }
	private:
		sf::Sprite sprite;
		ProjectileAnimation* animation;
		bool destroyed;
		bool moveRight;
		float veloX;
		float veloY;
		float X;
		float Y;
};

class ProjectileManager {
	public:
	ProjectileManager();
	void addProjectile(sf::Texture& texture, float veloX, float veloY, float x, float y, bool mr);
	void update(float deltatime);
	void draw(sf::RenderWindow& window);
	void destroyProjectile(int index);
	void destroyAll();
	std::vector<Projectile*>& getProjectiles();
	private:
	std::vector<Projectile*> projectiles;
};

