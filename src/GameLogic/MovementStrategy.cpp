#include"MovementStrategy.h"


void PatrolMovement::move(sf::Sprite& sprite, float deltatime, 
  std::vector<std::string>& mapData, int tileSize)
  {
  const float speed = 50.f;
  sf::Vector2f prevPosition = sprite.getPosition();
  sf::Vector2f nextPosition = prevPosition;
  nextPosition.x += speed * direction * deltatime;
 // std::cout << nextPosition.x << std::endl;
  // Calculate grid positions
  int prevGridX = static_cast<int>(prevPosition.x / tileSize);
  int prevGridY = static_cast<int>(prevPosition.y / tileSize);
  int nextGridX = static_cast<int>(nextPosition.x / tileSize);
  int nextGridY = static_cast<int>(nextPosition.y / tileSize);
  //std::cout << nextGridY << std::endl;
  // Check for collision
  if (nextGridX <= 0 || nextGridX >= mapData[0].size() || nextGridY <= 0 ||
      nextGridY >= mapData.size() || (mapData[nextGridY][nextGridX] != '0' && mapData[nextGridY][nextGridX]!='M')) {
      direction = -direction;  // Reverse direction on collision
  }
  else if (direction > 0 && (mapData[nextGridY][nextGridX+1] != '0' &&
                             mapData[nextGridY][nextGridX + 1] != 'M')) {
    direction = -direction;
  }
  else {
    int rightX = static_cast<int>((nextPosition.x + tileSize) / tileSize);
    int bottomY = static_cast<int>((nextPosition.y + tileSize) / tileSize);
    if (mapData[bottomY][rightX] == '0') {
      direction = -direction;

    }
      // Update sprite position
      sprite.setPosition(nextPosition);

  }
    //check for throw
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

XYmovement::XYmovement(sf::Vector2f velocity, float movementrange, float initialX)
{
  this->velocity = velocity;
  this->movementrange = movementrange;
  this->initialX = initialX;
}

void XYmovement::move(sf::Sprite& sprite,float deltatime,std::vector<std::string>& mapData, int tileSize)
{
  // Current and predicted positions
  sf::Vector2f prevPosition = sprite.getPosition();
  sf::Vector2f nextPosition = prevPosition + velocity * deltatime;

  // Convert positions to grid coordinates
  int prevGridX = static_cast<int>(prevPosition.x / tileSize);
  int prevGridY = static_cast<int>(prevPosition.y / tileSize);
  int nextGridX = static_cast<int>(nextPosition.x / tileSize);
  int nextGridY = static_cast<int>(nextPosition.y / tileSize);
  int rightX = static_cast<int>((nextPosition.x + tileSize) / tileSize);
  int bottomY = static_cast<int>((nextPosition.y + tileSize) / tileSize);
  int middleX = static_cast<int>((nextPosition.x + tileSize / 2) / tileSize);
  int middleY = static_cast<int>((nextPosition.y + tileSize / 2) / tileSize);

  // Check X-axis collision
  if (nextGridX <= 0 || nextGridX >= mapData[0].size()-1 || 
      (mapData[prevGridY][nextGridX] != '0' &&
       mapData[prevGridY][nextGridX] != 'B')) {
    velocity.x = -velocity.x;         
    nextPosition.x = prevPosition.x; 
    direction = -direction;
  }

  // Check Y-axis collision
  if (nextGridY <= 0 || nextGridY >= mapData.size()-1 ||
      (mapData[nextGridY][prevGridX] != '0' &&
       mapData[nextGridY][prevGridX] != 'B')) {
    velocity.y = -velocity.y;       
    nextPosition.y = prevPosition.y; 
    direction = -direction;
  }

  if (bottomY <= 0 || bottomY >= mapData.size() -1 || (mapData[bottomY][rightX] != '0' && mapData[bottomY][rightX] != 'B') || (mapData[bottomY][nextGridX] != '0' && mapData[bottomY][nextGridX] != 'B') ) {
	velocity.y = -velocity.y;       
	nextPosition.y = prevPosition.y; 
	direction = -direction;
  }

  if (rightX <= 0 || rightX >= mapData[0].size() -1 ||(mapData[middleY][rightX] != '0' && mapData[middleY][rightX] != 'B')) {
      velocity.x = -velocity.x;
      nextPosition.x = prevPosition.x;
      direction = -direction;
  }


  // Update sprite position
  sprite.setPosition(nextPosition);

  // Update map data if the sprite moves to a new grid
  //if (nextGridX != prevGridX || nextGridY != prevGridY) {
  //  // Clear previous tile
  //  if (mapData[prevGridY][prevGridX] == 'B') {
  //    mapData[prevGridY][prevGridX] = '0';
  //  }

  //  // Mark current tile
  //  if (mapData[nextGridY][nextGridX] == '0') {
  //    mapData[nextGridY][nextGridX] = 'B';
  //  }
  //}
}

UpDownmovement::UpDownmovement(sf::Vector2f velocity,
                               float movementrange,
                               float initialX)
{
  this->velocity = velocity;
  this->movementrange = movementrange;
  this->initialX = initialX;
}

void UpDownmovement::move(sf::Sprite& sprite,
                      float deltatime,
                      std::vector<std::string>& mapData,
                      int tileSize)
{
  // Current and predicted positions
  sf::Vector2f prevPosition = sprite.getPosition();
  sf::Vector2f nextPosition = prevPosition + velocity * deltatime;

  // Convert positions to grid coordinates
  int prevGridX = static_cast<int>(prevPosition.x / tileSize);
  int prevGridY = static_cast<int>(prevPosition.y / tileSize);
  int nextGridX = static_cast<int>(nextPosition.x / tileSize);
  int nextGridY = static_cast<int>(nextPosition.y / tileSize);
  int rightX = static_cast<int>((nextPosition.x + tileSize) / tileSize);
  int bottomY = static_cast<int>((nextPosition.y + tileSize) / tileSize);
  int middleX = static_cast<int>((nextPosition.x + tileSize / 2) / tileSize);
  int middleY = static_cast<int>((nextPosition.y + tileSize / 2) / tileSize);

  // Check X-axis collision
  if (nextGridX <= 0 || nextGridX >= mapData[0].size() - 1 ||
      nextGridX >= movementrange || nextGridX <= initialX ||
      (mapData[prevGridY][nextGridX] != '0' &&
       mapData[prevGridY][nextGridX] != 'B')) {
    velocity.x = -velocity.x;
    nextPosition.x = prevPosition.x;
    direction = -direction;
  }

  // Check Y-axis collision
  if (nextGridY <= 0 || nextGridY >= mapData.size() - 1 ||
      (mapData[nextGridY][prevGridX] != '0' &&
       mapData[nextGridY][prevGridX] != 'B')) {
    velocity.y = -velocity.y;
    nextPosition.y = prevPosition.y;
    direction = -direction;
  }

  if (bottomY <= 0 || bottomY >= mapData.size() - 1 ||
      (mapData[bottomY][rightX] != '0' && mapData[bottomY][rightX] != 'B') ||
      (mapData[bottomY][nextGridX] != '0' &&
       mapData[bottomY][nextGridX] != 'B')) {
    velocity.y = -velocity.y;
    nextPosition.y = prevPosition.y;
    direction = -direction;
  }

  if (rightX <= 0 || rightX >= mapData[0].size() - 1 ||
      (mapData[middleY][rightX] != '0' && mapData[middleY][rightX] != 'B')) {
    velocity.x = -velocity.x;
    nextPosition.x = prevPosition.x;
    direction = -direction;
  }

  // Update sprite position
  sprite.setPosition(nextPosition);

}
