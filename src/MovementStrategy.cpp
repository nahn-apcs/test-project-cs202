#include"MovementStrategy.h"

void PatrolMovement::move(sf::Sprite& sprite, float deltatime)
{
  static float direction = 1.f;
  sprite.move(50.f * direction * deltatime, 0.f);
  if (sprite.getPosition().x > 800 || sprite.getPosition().x < 0)
	direction = -direction;

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

void JumpupMovement::move(sf::Sprite& sprite, float deltatime)
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

