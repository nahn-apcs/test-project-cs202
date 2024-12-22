#pragma once

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include <iostream>
Projectile::Projectile(sf::Texture& texture, float veloX, float veloY, float x, float y, bool mr) :veloX(veloX), veloY(veloY), X(x), Y(y) {
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
			sprite.move(veloX * deltatime, veloY*deltatime);
		}
		else {
			sprite.move(-veloX * deltatime, veloY*deltatime);
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

void ProjectileManager::addProjectile(sf::Texture& texture, float veloX, float veloY, float x, float y, bool mr) {
	projectiles.push_back(new Projectile(texture, veloX , veloY, x, y, mr));
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
	projectiles[index]->destroy();
}

void ProjectileManager::destroyAll() {
	projectiles.clear();
}

std::vector<Projectile*>& ProjectileManager::getProjectiles() {
	return projectiles;
}


