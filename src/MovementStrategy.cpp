#include"MovementStrategy.h"


void PatrolMovement::move(sf::Sprite& sprite, float deltatime, 
  std::vector<std::string>& mapData, int tileSize)
  {
  const float speed = 50.f;
  sf::Vector2f prevPosition = sprite.getPosition();
  sf::Vector2f nextPosition = prevPosition;
  nextPosition.x += speed * direction * deltatime;

  // Calculate grid positions
  int prevGridX = static_cast<int>(prevPosition.x / tileSize);
  int prevGridY = static_cast<int>(prevPosition.y / tileSize);
  int nextGridX = static_cast<int>(nextPosition.x / tileSize);
  int nextGridY = static_cast<int>(nextPosition.y / tileSize);

  // Check for collision
  if (nextGridX < 0 || nextGridX >= mapData[0].size() || nextGridY < 0 ||
      nextGridY >= mapData.size() || mapData[nextGridY][nextGridX] == 'P' || mapData[nextGridY][nextGridX] == 'p') {
      direction = -direction;  // Reverse direction on collision
  }
  else {
    // Update sprite position
    sprite.setPosition(nextPosition);

    // Update mapData if the monster "occupies" a new tile
    if (nextGridX != prevGridX || nextGridY != prevGridY) {
      // Clear previous tile
      if (mapData[prevGridY][prevGridX] == 'M') {
        mapData[prevGridY][prevGridX] = '0';  
      }

      if (mapData[nextGridY][nextGridX] == '0')
      mapData[nextGridY][nextGridX] = 'M';
    }
  }
  }



JumpupMovement::JumpupMovement(float jumpHeight, float jumpInterval)
{
  this->jumpHeight = jumpHeight;
  this->jumpInterval = jumpInterval;
  elapsedTime = 0.f;
  isJumping = false;
  initialY = 0.f;
  velocityY = 0.f;
}

void JumpupMovement::move(sf::Sprite& sprite,
                          float deltatime,
                          std::vector<std::string>& mapData,
                          int tileSize)
{
  elapsedTime += deltatime;
  if (!isJumping && elapsedTime >= jumpInterval)
  {
      isJumping = true;
	  initialY = sprite.getPosition().y;
	  velocityY = sqrtf(2.0f * gravity * jumpHeight);
      elapsedTime = 0.f;
  }
  if (isJumping) {
    float deltaY = velocityY * elapsedTime - 0.5f * gravity * elapsedTime * elapsedTime;
    sprite.setPosition(sprite.getPosition().x, initialY - deltaY);
    if (deltaY <= 0) {
      isJumping = false;
      sprite.setPosition(sprite.getPosition().x, initialY);
    }
  }
}

