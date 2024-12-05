#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Character.h"

class Physics {
public:
    static bool checkCollision(const sf::FloatRect& playerBounds, Map& map, int tileSize);
    static void handleCollisions(Character& character, Map& map, float deltaTime);
};

#endif // PHYSICS_H
