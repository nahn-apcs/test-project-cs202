#include "Character.h"
#include "Map.h"
#include "render.h"

Character::Character(std::vector<sf::Texture>& idleTextures, std::vector<sf::Texture>& runTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& srunTextures, std::vector<sf::Texture>& sattackTextures, std::vector<sf::Texture>& jumpT, std::vector<sf::Texture>& sidleTextures, std::vector<sf::Texture>& sjumpT, int x, int y)
: velocityX(0), velocityY(0), onGround(false), isJumping(false), attacking(false), faceRight(true) {

    idleAnimations.push_back(new Animation(idleTextures, 0.1f));
    idleAnimations.push_back(new Animation(sidleTextures, 0.1f));
    runAnimations.push_back(new Animation(runTextures, 0.1f));
    runAnimations.push_back(new Animation(srunTextures, 0.1f));
    attackAnimations.push_back(new Animation(attackTextures, 0.1f));
    attackAnimations.push_back(new Animation(sattackTextures, 0.1f));
    jumpAnimations.push_back(new Animation(jumpT, 0.1f));
    jumpAnimations.push_back(new Animation(sjumpT, 0.1f));
    sprite.setPosition(x, y);
}

void Character::shoot(Map* map) {
	// Get the position of the character
	sf::Vector2f position = sprite.getPosition();
	// Create a new projectile
    if (faceRight) {
		map->projectiles.addProjectile(map->getProjectileTexture(), 400.0f, position.x + getBounds().width, position.y + getBounds().height/2, true);
	}
    else {
        map->projectiles.addProjectile(map->getProjectileTexture(), 400.0f, position.x, position.y + getBounds().height / 2, false);
    }
}

void Character::interact(float deltatime, Map* map) {
    // Handle movement

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        increaseSpeed();
    }
    else
    {
        moveSpeed = 100.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        setVelocityX(-moveSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        setVelocityX(moveSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        jump();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		if (cooldown <= 0 && level >= 2) {
			shoot(map);
			cooldown = 1.0f;
            attacking = true;
		}
	}


}

void Character::increaseSpeed() {
    moveSpeed = 200.0f;
}

void Character::drawBounds(sf::RenderWindow& window) {
    // Get the bounding box of the sprite
    sf::FloatRect bounds = getBounds();

    // Create a rectangle shape that matches the bounds
    sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
    rect.setPosition(bounds.left, bounds.top);
    rect.setOutlineColor(sf::Color::Red);  // Red color for the bounding box
    rect.setOutlineThickness(2);  // Set the outline thickness
    rect.setFillColor(sf::Color::Transparent);  // Set fill color to transparent

    // Draw the bounding box
    window.draw(rect);
}

void Character::update(float deltaTime, Map* map) {
    applyGravity(deltaTime);
    applyFriction(deltaTime);
    //std::cout << "velocityX: " << velocityX << std::endl;
    if (cooldown > 0) {
		cooldown -= deltaTime;
        if (cooldown > 0.75f) {
            attacking = true;
        }
        else {
			attacking = false;
		}
	}
    onGround = false; // Assume the character is not on the ground

    if (velocityX > 0) {
        faceRight = true;
    }
    else if (velocityX < 0) {
        faceRight = false;
    }

    // Check if we are about to hit a wall before moving
    if (velocityX == 0) {
        if (attacking)
		{
			attackAnimations[status]->update(deltaTime);
            attackAnimations[status]->applyToSprite(sprite, faceRight);
		}
		else {
			idleAnimations[status]->update(deltaTime);
			idleAnimations[status]->applyToSprite(sprite, faceRight);
		}
    }

    if (!checkWallCollision(velocityX * deltaTime, 0.f, map)) {
        sprite.move(velocityX * deltaTime, 0);
        if (attacking)
        {
            attackAnimations[status]->update(deltaTime);
            attackAnimations[status]->applyToSprite(sprite, faceRight);
        }
        else if (velocityX != 0) {
            runAnimations[status]->update(deltaTime);
            runAnimations[status]->applyToSprite(sprite, faceRight);
        }
    }


    // Move vertically
    if (!onGround) {
        if (isJumping) {
			jumpAnimations[status]->update(deltaTime);
			jumpAnimations[status]->applyToSprite(sprite, faceRight);
		}
		else {
			jumpAnimations[status]->update(deltaTime);
			jumpAnimations[status]->applyToSprite(sprite, faceRight);
		}
        if (!checkWallCollision(0, velocityY * deltaTime, map)) sprite.move(0, velocityY * deltaTime);
        else {
            velocityY = 0;
        }
    }
    handleCollisions(map);

}

void Character::move(float dx, float dy, Map* map) {
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
    sf::FloatRect temp = sprite.getGlobalBounds();
    temp.left += 15.f;
    temp.width -= 32.f;
    //std::cout << "left: " << temp.left << " top: " << temp.top << " width: " << temp.width << " height: " << temp.height << std::endl;
    //std::cout << "left: " << sprite.getGlobalBounds().left << " top: " << sprite.getGlobalBounds().top << " width: " << sprite.getGlobalBounds().width << " height: " << sprite.getGlobalBounds().height << std::endl;
    return temp;
}

void Character::applyGravity(float deltaTime) {
    if (!onGround) {
        velocityY += gravity * deltaTime;
    }
}

void Character::applyFriction(float deltaTime) {
    /*if (onGround) {
        if (velocityX > 0) {
            velocityX -= 5.0f*deltaTime;
            if (velocityX < 0) velocityX = 0;
        }
        else if (velocityX < 0) {
            velocityX += 5.0f*deltaTime;
            if (velocityX > 0) velocityX = 0;
        }
    }*/
    //std::cout << "velocityX: " << velocityX << std::endl;
    if (velocityX > 0) {
        velocityX -= 100.0f * deltaTime;
        if (velocityX < 0) velocityX = 0;
    }
    else if (velocityX < 0) {
        velocityX += 100.0f * deltaTime;
        if (velocityX > 0) velocityX = 0;
    }

}

void Character::handleCollisions(Map* map) {
    // Handle vertical collisions (ground and ceiling)

    // Check for collisions with ground (stop falling)
    sf::FloatRect bounds = getBounds();
    int tileX = bounds.left / map->getTileSize();
    int tileY = (bounds.top + bounds.height) / map->getTileSize();
    int rightTileX = (bounds.left + bounds.width) / map->getTileSize();
    int topTileY = bounds.top / map->getTileSize();
    int middleTileY = (bounds.top + bounds.height / 2) / map->getTileSize();
    int middleTileX = (bounds.left + bounds.width / 2) / map->getTileSize();

    //std::cout << "tileX: " << tileX << " tileY: " << tileY << std::endl;
    // Check for collision with ground (the tile at the bottom of the character)
    if (tileY < map->getMapData().size() && tileX < map->getMapData()[tileY].size()) {
        char tile = map->getMapData()[tileY][middleTileX];
        char rigthTile = map->getMapData()[tileY][rightTileX];
        char leftTile = map->getMapData()[tileY][tileX];
        if (!map->colliableChar(tile) || !map->colliableChar(leftTile) || !map->colliableChar(rigthTile)) { // Colliding with the ground
            onGround = true;
            velocityY = 0;
            //sprite.setPosition(bounds.left, tileY * map->getTileSize() - bounds.height); // Adjust position to be on top of the tile
        }
        //char rightTile = map->getMapData()[tileY][rightTileX];
        //if (rightTile != '0') { // Colliding with the ground
        //	onGround = true;
        //	velocityY = 0;
        //	//sprite.setPosition(bounds.left, tileY * map->getTileSize() - bounds.height); // Adjust position to be on top of the tile
        //}
    }

    // Check for ceiling collision (stopping upward movement during jumps)
    int ceilingTileY = bounds.top / map->getTileSize();
    if (ceilingTileY >= 0 && tileX < map->getMapData()[ceilingTileY].size()) {
        char ceilingTile = map->getMapData()[ceilingTileY][tileX];
        if (!map->colliableChar(ceilingTile) && velocityY < 0) { // Stop upward movement
            velocityY = 0;
        }
    }

    // Handle horizontal collisions (left and right walls)
    if (tileX < 0 || tileY < 0 || tileY >= map->getMapData().size()) {
        velocityX = 0; // Stop horizontal movement
    }

    if (rightTileX >= map->getMapData()[0].size() || topTileY < 0 || topTileY >= map->getMapData().size()) {
        velocityX = 0; // Stop horizontal movement
    }


    // Check if moving left or right would cause the character to hit a wall
    if (tileX >= 0 && tileX < map->getMapData()[0].size()) {
        char tile = map->getMapData()[tileY][tileX];
        if (!map->colliableChar(tile)) {
            //std::cout << "Stop tile: " << tileX << " " << tileY <<" " << tile << std::endl;
            velocityX = 0; // Stop horizontal movement
        }
    }

    if (rightTileX >= 0 && rightTileX < map->getMapData()[0].size()) {
        char tile = map->getMapData()[tileY][rightTileX];
        if (!map->colliableChar(tile)) {
            //std::cout << "Stop tile: " << rightTileX << " " << tileY << " " << tile << std::endl;
            velocityX = 0; // Stop horizontal movement
        }
    }

    if (rightTileX >= 0 && rightTileX < map->getMapData()[0].size()) {
		if(checkWallCollision(velocityX, 0, map) == 4 || checkWallCollision(velocityX, 0, map) == 8) {
			velocityX = 0;
		}

	}

}


int Character::checkWallCollision(float dx, float dy, Map* map) {
    sf::FloatRect bounds = getBounds();

    int newX = bounds.left + dx;
    int newY = bounds.top + dy;
    int newRight = newX + bounds.width;
    int newBottom = newY + bounds.height - 1.0f;
    // Check collision in the new position
    int tileX = newX / map->getTileSize();
    int tileY = newY / map->getTileSize();
    int rightTileX = newRight / map->getTileSize();
    int bottomTileY = newBottom / map->getTileSize();
    int middleTileY = (newY + bounds.height / 2) / map->getTileSize();
    int middleTileX = (newX + bounds.width / 2) / map->getTileSize();
    //std::cout << "tileX: " << tileX << " tileY: " << tileY << std::endl;

    if (bottomTileY >= map->getMapData().size()) {
        return -1;
    }

    // Check if the new position is outside the map
    if (rightTileX >= map->getMapData()[0].size() || bottomTileY >= map->getMapData().size()) {
        //std::cout << "Check 1 -1" << std::endl;

        return -1; // Collision detected
    }

    if (tileX <= 0 || tileY <= 0 || tileY >= map->getMapData().size()) {
        //std::cout << tileX << " " << tileY << std::endl;
        //std::cout << "Check 2 -1" << std::endl;

        return -1;
    }

    std::vector<int> check(2);
    //std::cout << "Check 0" << std::endl;


    // Check if the new position collides with the wall (tile == '1')
    if (tileX >= 0 && tileX < map->getMapData()[0].size() && tileY >= 0 && tileY < map->getMapData().size()) {
        if (map->getMapData()[tileY][tileX] != '0' && map->getMapData()[tileY][tileX] != 'C') {
            //std::cout << "Check 1" << std::endl;
            return 1; // Collision detected
        }
    }

    if (rightTileX >= 0 && rightTileX < map->getMapData()[0].size() && tileY >= 0 && tileY < map->getMapData().size()) {
        if (map->getMapData()[tileY][rightTileX] != '0' && map->getMapData()[tileY][rightTileX] != 'C') {
            //std::cout << "Check 2" << std::endl;
            return 2; // Collision detected
        }
    }

    if (tileX >= 0 && tileX < map->getMapData()[0].size() && bottomTileY >= 0 && bottomTileY < map->getMapData().size()) {
        if (map->getMapData()[bottomTileY][tileX] != '0' && map->getMapData()[bottomTileY][tileX] != 'C') {
            //std::cout << "Check 3" << std::endl;

            return 3; // Collision detected
        }
    }

    if (rightTileX >= 0 && rightTileX < map->getMapData()[0].size() && bottomTileY >= 0 && bottomTileY < map->getMapData().size()) {
        if (map->getMapData()[bottomTileY][rightTileX] != '0' && map->getMapData()[bottomTileY][rightTileX] != 'C') {
            //std::cout << "Check 4" << std::endl;

            return 4; // Collision detected
        }
    }

    if (middleTileX >= 0 && middleTileX < map->getMapData()[0].size() && middleTileY >= 0 && middleTileY < map->getMapData().size()) {
        if (map->getMapData()[tileY][middleTileX] != '0' && map->getMapData()[tileY][middleTileX] != 'C') {
            //std::cout << "Check 5" << std::endl;

            return 5; // Collision detected
        }
    }

    if (middleTileX >= 0 && middleTileX < map->getMapData()[0].size() && middleTileY >= 0 && middleTileY < map->getMapData().size()) {
        if (map->getMapData()[middleTileY][rightTileX] != '0' && map->getMapData()[middleTileY][rightTileX] != 'C') {
            //std::cout << "Check 6" << std::endl;

            return 6; // Collision detected
        }
    }

    if (middleTileX >= 0 && middleTileX < map->getMapData()[0].size() && middleTileY >= 0 && middleTileY < map->getMapData().size()) {
        if (map->getMapData()[bottomTileY][middleTileX] != '0' && map->getMapData()[bottomTileY][middleTileX] != 'C') {
            //std::cout << "Check 7" << std::endl;

            return 7; // Collision detected
        }
    }

    if (middleTileX >= 0 && middleTileX < map->getMapData()[0].size() && middleTileY >= 0 && middleTileY < map->getMapData().size()) {
        if (map->getMapData()[middleTileY][tileX] != '0' && map->getMapData()[middleTileY][tileX] != 'C') {
            //std::cout << "Check 8" << std::endl;

            return 8; // Collision detected
        }
    }

    return false; // No collision
}

Character::~Character() {
	for (auto& anim : idleAnimations) {
		delete anim;
	}
    for (auto& anim : runAnimations) {
		delete anim;
	}
    for (auto& anim : attackAnimations) {
		delete anim;
	}
	for (auto& anim : jumpAnimations) {
		delete anim;
	}
}

void Character::pushBack(Map* map){
    setVelocityY(-100.0f);
    setVelocityX(-100.0f);
}

void Character::dead(Map* map){
	//
}

void Character::damaged(Map* map){
    pushBack(map);
	if (level > 0) level--;
    if (level == 1) status = 1;
	if (level == 0) {
        dead(map);
	}
}

void Character::levelUp(Map* map){
	level++;
    if (level >= 2) status = 2;
}