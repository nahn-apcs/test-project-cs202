#include "Physics.h"

bool Physics::checkCollision(const sf::FloatRect& playerBounds, Map& map, int tileSize) {
    int col = playerBounds.left / tileSize;
    int row = playerBounds.top / tileSize;
    std::vector<std::string> mapData = map.getMapData();
    if (mapData[row][col] == '1') {
        return false;
    }
    return false;
}

void Physics::handleCollisions(Character& character, Map& map, float deltaTime) {
    sf::FloatRect bounds = character.getBounds();
    character.jump();  // Ready to jump again

    // Check for ground collision (bottom collision)
    if (checkCollision(bounds, map, 32)) {
        // Reset vertical velocity to 0 and position to be on top of the tile
        character.move(0, -50, map);  // Adjust based on tile height
        character.jump();  // Ready to jump again
        character.jump();  // Ready to jump again
        character.jump();  // Ready to jump again
    }
}
