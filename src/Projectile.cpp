#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <iostream>
Projectile::Projectile(sf::Texture& texture, float speed, float x, float y, bool mr) :speed(speed), X(x), Y(y) {
	moveRight = mr;
	destroyed = false;
	sprite.setTexture(texture);
	sprite.setPosition(x, y);

	animation = new ProjectileAnimation(sprite, 0.1f, mr);
	animation->addFrame(sf::IntRect(0, 0, 16, 16));
	animation->addFrame(sf::IntRect(16, 0, 16, 16));

	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
}

void Projectile::update(float deltatime) {
	
	if (!destroyed) {
		animation->update(deltatime);
		animation->applyToSprite(sprite, moveRight);
		if (moveRight) {
			sprite.move(speed * deltatime, 0.0f);
		}
		else {
			sprite.move(-speed * deltatime, 0.0f);
		}
	}
}


void Projectile::draw(sf::RenderWindow& window) {
	if (!destroyed) {		window.draw(sprite);
	}
}

sf::FloatRect Projectile::getBounds() const {
	return sprite.getGlobalBounds();
}

bool Projectile::isDestroyed() const {
	return destroyed;
}

void Projectile::destroy() {
	destroyed = true;
}

ProjectileManager::ProjectileManager() {
}

void ProjectileManager::addProjectile(sf::Texture& texture, float speed, float x, float y, bool mr) {
	projectiles.push_back(new Projectile(texture, speed, x, y, mr));
}

void ProjectileManager::update(float deltatime) {
	for (int i = 0; i < projectiles.size(); ++i) {
		projectiles[i]->update(deltatime);
	}
}

void ProjectileManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < projectiles.size(); ++i) {
		projectiles[i]->draw(window);
	}
}

void ProjectileManager::destroyProjectile(int index) {
	projectiles.erase(projectiles.begin() + index);
}

void ProjectileManager::destroyAll() {
	projectiles.clear();
}

std::vector<Projectile*>& ProjectileManager::getProjectiles() {
	return projectiles;
}


