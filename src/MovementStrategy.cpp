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
  if (nextGridX < 0 || nextGridX >= mapData[0].size() || nextGridY < 0 ||
      nextGridY >= mapData.size() || (mapData[nextGridY][nextGridX] != '0' && mapData[nextGridY][nextGridX]!='M')) {
      direction = -direction;  // Reverse direction on collision
  }
  else if (direction > 0 && (mapData[nextGridY][nextGridX+1] != '0' &&
                             mapData[nextGridY][nextGridX + 1] != 'M')) {
    direction = -direction;
  }
  else {
    if (mapData[nextGridY + 1][prevGridX] != '0') {
      if (mapData[nextGridY + 1][nextGridX] == '0') {
          direction = -direction;
        
      }
    }
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

XYmovement::XYmovement(sf::Vector2f velocity)
{
  this->velocity = velocity;
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

  // Check X-axis collision
  if (nextGridX <= 0 || nextGridX >= mapData[0].size()-1 ||
      (mapData[prevGridY][nextGridX] != '0' &&
       mapData[prevGridY][nextGridX] != 'B')) {
    velocity.x = -velocity.x;         
    nextPosition.x = prevPosition.x;  
  }

  // Check Y-axis collision
  if (nextGridY <= 0 || nextGridY >= mapData.size()-1 ||
      (mapData[nextGridY][prevGridX] != '0' &&
       mapData[nextGridY][prevGridX] != 'B')) {
    velocity.y = -velocity.y;       
    nextPosition.y = prevPosition.y;  
  }

  // Update sprite position
  sprite.setPosition(nextPosition);

  // Update map data if the sprite moves to a new grid
  if (nextGridX != prevGridX || nextGridY != prevGridY) {
    // Clear previous tile
    if (mapData[prevGridY][prevGridX] == 'B') {
      mapData[prevGridY][prevGridX] = '0';
    }

    // Mark current tile
    if (mapData[nextGridY][nextGridX] == '0') {
      mapData[nextGridY][nextGridX] = 'B';
    }
  }
}

UpDownmovement::UpDownmovement(float initialY,float speed, float movementRange)
{
  this->initialY = initialY;
  this->speed = speed;
  this->movementrange = movementRange;
}

void UpDownmovement::move(sf::Sprite& sprite,
                          float deltatime,
                          std::vector<std::string>& mapData,
                          int tileSize)
{
  // Current and predicted positions
  sf::Vector2f prevPosition = sprite.getPosition();
  sf::Vector2f nextPosition = prevPosition;
  nextPosition.y += speed * direction * deltatime;

  // Convert positions to grid coordinates
  int prevGridX = static_cast<int>(prevPosition.x / tileSize);
  int prevGridY = static_cast<int>(prevPosition.y / tileSize);
  int nextGridX = static_cast<int>(nextPosition.x / tileSize);
  int nextGridY = static_cast<int>(nextPosition.y / tileSize);

  if (nextPosition.y > initialY + movementrange) {
    direction = -1.0f;                     
  }
  else if (nextPosition.y < initialY) {
    nextPosition.y = initialY;  
    direction = 1.0f;       
  }

  
  sprite.setPosition(nextPosition);

  // Update map data if the sprite moves to a new grid
  if (nextGridX != prevGridX || nextGridY != prevGridY) {
    // Clear previous tile
    if (mapData[prevGridY][prevGridX] == 'T') {
      mapData[prevGridY][prevGridX] = '0';
      std::cout << "clear" << std::endl;
    }

    // Mark current tile
    if (mapData[nextGridY][nextGridX] == '0') {
      mapData[nextGridY][nextGridX] = 'T';
    }
  }

}