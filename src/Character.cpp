#include "Character.h"
#include "Map.h"
#include "render.h"

Character::Character(sf::Texture& texture, int x, int y)
    : velocityX(0), velocityY(0), onGround(false), isJumping(false)
{
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Character::update(float deltaTime, const Map& map) {
    applyGravity(deltaTime);
    onGround = false; // Assume the character is not on the ground
    // Check if we are about to hit a wall before moving
    if (!checkWallCollision(velocityX*deltaTime, 0.f, map)) {
        sprite.move(velocityX*deltaTime, 0); // Horizontal movement
    }

    // Move vertically
    if (!onGround ) {
        if (!checkWallCollision(0, velocityY * deltaTime, map)) sprite.move(0, velocityY*deltaTime); // Falling or jumping
        else {
			velocityY = 0;
		}
    }

    handleCollisions(map);
}

void Character::move(float dx, float dy, const Map& map) {
    if (!checkWallCollision(dx, dy, map)) {
		sprite.move(dx, dy);
	}
}


void Character::jump() {
    if (onGround) {
        velocityY = jumpStrength;
        onGround = false;
    }
}

void Character::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Character::getBounds() const {
    return sprite.getGlobalBounds();
}

void Character::applyGravity(float deltaTime) {
    if (!onGround) {
        velocityY += gravity*deltaTime;
    }
}

void Character::handleCollisions(const Map& map) {
    // Handle vertical collisions (ground and ceiling)

    // Check for collisions with ground (stop falling)
    sf::FloatRect bounds = sprite.getGlobalBounds();
    int tileX = bounds.left / map.getTileSize();
    int tileY = (bounds.top + bounds.height) / map.getTileSize();
    //std::cout << "tileX: " << tileX << " tileY: " << tileY << std::endl;
    // Check for collision with ground (the tile at the bottom of the character)
    if (tileY < map.getMapData().size() && tileX < map.getMapData()[tileY].size()) {
        char tile = map.getMapData()[tileY][tileX];
        if (tile == '1') { // Colliding with the ground
            onGround = true;
            velocityY = 0;
            sprite.setPosition(bounds.left, tileY * map.getTileSize() - bounds.height); // Adjust position to be on top of the tile
        }
    }

    // Check for ceiling collision (stopping upward movement during jumps)
    int ceilingTileY = bounds.top / map.getTileSize();
    if (ceilingTileY >= 0 && tileX < map.getMapData()[ceilingTileY].size()) {
        char ceilingTile = map.getMapData()[ceilingTileY][tileX];
        if (ceilingTile == '1' && velocityY < 0) { // Stop upward movement
            velocityY = 0;
        }
    }

    // Handle horizontal collisions (left and right walls)
    if (tileX < 0 || tileY < 0 || tileY >= map.getMapData().size()) {
        velocityX = 0; // Stop horizontal movement
    }

    
    // Check if moving left or right would cause the character to hit a wall
    if (tileX >= 0 && tileX < map.getMapData()[0].size()) {
        char tile = map.getMapData()[tileY][tileX];
        if (tile == '1') {
            velocityX = 0; // Stop horizontal movement
        }
    }
}


int Character::checkWallCollision(float dx, float dy, const Map& map) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    int newX = bounds.left + dx;
    int newY = bounds.top + dy;
    int newRight = newX + bounds.width;
    int newBottom = newY + bounds.height-5.0f;
    // Check collision in the new position
    int tileX = newX / map.getTileSize();
    int tileY = newY / map.getTileSize();
    int rightTileX = newRight / map.getTileSize();
    int bottomTileY = newBottom / map.getTileSize();
    //std::cout << "tileX: " << tileX << " tileY: " << tileY << std::endl;


    // Check if the new position is outside the map
    if (rightTileX >= map.getMapData()[0].size() || bottomTileY >= map.getMapData().size()) {
		return -1; // Collision detected
	}

    if (tileX <= 0 || tileY <= 0 || tileY >= map.getMapData().size()) {
		return -1; 
	}

    

    // Check if the new position collides with the wall (tile == '1')
    if (tileX >= 0 && tileX < map.getMapData()[0].size() && tileY >= 0 && tileY < map.getMapData().size()) {
        if (map.getMapData()[tileY][tileX] == '1') {
            return 1; // Collision detected
        }
    }

    if (rightTileX >= 0 && rightTileX < map.getMapData()[0].size() && tileY >= 0 && tileY < map.getMapData().size()) {
		if (map.getMapData()[tileY][rightTileX] == '1') {
			return 2; // Collision detected
		}
	}

    if (tileX >= 0 && tileX < map.getMapData()[0].size() && bottomTileY >= 0 && bottomTileY < map.getMapData().size()) {
        if (map.getMapData()[bottomTileY][tileX] == '1') {
            return 3; // Collision detected
		}
    }

    if (rightTileX >= 0 && rightTileX < map.getMapData()[0].size() && bottomTileY >= 0 && bottomTileY < map.getMapData().size()) {
		if (map.getMapData()[bottomTileY][rightTileX] == '1') {
			return 4; // Collision detected
		}
	}
    return false; // No collision
}
