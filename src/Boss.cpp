//public:
//	Boss() = default;
//	Boss(std::vector<sf::Texture>& flyTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& dieTextures, std::vector<sf::Texture>& exhaustTextures, std::vector<sf::Texture>& shootTextures, int x, int y);
//	~Boss();
//	void update(float deltaTime, Map* map);
//	void move(float dx, float dy, Map* map);
//	void pushBack(Map*);
//	void dead(Map*);
//	void shoot(Map* map);
//	void draw(sf::RenderWindow& window);
//	void setVelocityX(float vx) { velocityX = vx; }
//	void setVelocityY(float vy) { velocityY = vy; }
//	void drawBounds(sf::RenderWindow& window);
//	void interact(float d, Map* map, float playerX, float playerY);
//	void damaged(Map* map);
//	sf::FloatRect getBounds() const;
//	bool isAttacking() const { return attacking; }
//	bool isDead() const { return Dead; }
//	void activate() { activated = true; }
//
//private:
//	sf::Sprite mSprite;
//	Animation* flyAnimation;
//	Animation* attackAnimation;
//	Animation* dieAnimation;
//	Animation* exhaustAnimation;
//	Animation* shootAnimation;
//
//
//	sf::Vector2f mPosition;
//	float velocityX;
//	float velocityY;
//	bool mIsMovingRight;
//	bool activated = false;
//	bool attacking;
//	bool Dead = false;
//	int health = 50;
//	int checkWallCollision(float dx, float dy, Map* map);
//
//};


#include "Boss.h"


Boss::Boss(std::vector<sf::Texture>& flyTextures, std::vector<sf::Texture>& attackTextures, std::vector<sf::Texture>& dieTextures, std::vector<sf::Texture>& exhaustTextures, std::vector<sf::Texture>& shootTextures, int x, int y)
{
	sprite.setTexture(flyTextures[0]);
	sprite.setPosition(x, y);
	sprite.setScale(2.f, 2.f);
	mPosition = sprite.getPosition();
	flyAnimation = new Animation(flyTextures, 0.5f);
	attackAnimation = new Animation(attackTextures, 0.3f);
	dieAnimation = new Animation(dieTextures, 0.5f);
	exhaustAnimation = new Animation(exhaustTextures, 0.5f);
	shootAnimation = new Animation(shootTextures, 0.3f);
}

Boss::~Boss()
{
	if (flyAnimation)
		delete flyAnimation;
	if (attackAnimation)
		delete attackAnimation;
	if (dieAnimation)
		delete dieAnimation;
	if (exhaustAnimation)
		delete exhaustAnimation;
	if (shootAnimation)
		delete shootAnimation;
}

void Boss::draw(sf::RenderWindow& window)
{
	 window.draw(sprite);
}

sf::FloatRect Boss::getBounds() const
{
	return sprite.getGlobalBounds();
}

void Boss::interact(float d, Map* map, sf::Vector2f player )
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}

		sf::Vector2f pos = getBounds().getPosition();
		float dx = pos.x - player.x;
		if (dx > 0) {
			mIsMovingRight = true;
		}
		else {
			mIsMovingRight = false;
		}
		
		if (cooldown > 0.f) {
			cooldown -= d;
		}
		else if (cooldown <= 0.f) {
			int random = rand()%5;
			switch (random)
			{
				case 0:
				circularShoot(map);
				break;
				case 1:
				angularShoot(map, player);
				break;
				case 2:
					rainShoot(map);
					break;
				case 3:
					groundShoot(map);
					break;
				case 4:
					shootFromFeet(map);
					break;

			default:
				break;
			}
			shootTime = 1.0f;
			cooldown = 4.0f;
		}

		if (moveTime > 0.f) {
			moveTime -= d;
		}
		else if (moveTime <= 0.f) {
			mPosition = sprite.getPosition();
			float dx = mPosition.x - player.x;
			float dy = mPosition.y - player.y;
			float distance = sqrt(dx * dx + dy * dy);
			 
				float vX = dx / 8.0f;
				float vY = dy / 8.0f;
				if (distance > 200.f) {
					setVelocityX(-vX);
					setVelocityY(-vY);
					//std::cout << vX << " " << vY << std::endl;
				}
			moveTime = 2.0f;
		}

		if (teleportTime > 0.f) {
			teleportTime -= d;
		}
		else if (teleportTime <= 0.f) {
			int random = rand() % 3;
			switch (random)
			{
			case 1:
				sprite.setPosition(325*32, 30);
				rainShoot(map);
				break;
			case 2:
				if (mIsMovingRight) {
					sprite.setPosition(player.x - 100.f, player.y - 170.f);
					normalAttack(map);
				}
				else {
					sprite.setPosition(player.x + 100.f, player.y - 170.f);
					normalAttack(map);
				}
				break;
			default:
				break;
			}
			teleportTime = 10.0f;
		}

		
	}
}

void Boss::shoot(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		sf::Vector2f position = sprite.getPosition();
		if (mIsMovingRight) {
			map->projectiles.addProjectile(map->getProjectileTexture(), 400.0f, 0.f, position.x + getBounds().width / 2, position.y + getBounds().height / 2, mIsMovingRight);
		}
		else {
			map->projectiles.addProjectile(map->getProjectileTexture(), -400.0f, 0.f, position.x + getBounds().width / 2, position.y + getBounds().height / 2, mIsMovingRight);
		}
		
	}
}


void Boss::update(float deltaTime, Map* map)
{
	if (activated) {
		if (health <= 0) {
			Dead = true;
			dieAnimation->update(deltaTime, false);
			dieAnimation->applyToSprite(sprite, mIsMovingRight);
			return;
		}
		if (exhaust) {
			exhaustAnimation->update(deltaTime, true);
			exhaustAnimation->applyToSprite(sprite, mIsMovingRight);
			if (exhaustTime > 0.f) {
				exhaustTime -= deltaTime;
			}
			else {
				exhaust = false;
			}
			return;
		}
		/////////////////////////////

		if (shootTime > 0.f) {
			shootTime -= deltaTime;
			shooting = true;
		}
		else {
			shooting = false;
		}

		if (attackTime > 0.f) {
			attackTime -= deltaTime;
			attacking = true;
		}
		else {
			attacking = false;
		}

		if (velocityX == 0) {
			flyAnimation->update(deltaTime, true);
			flyAnimation->applyToSprite(sprite, mIsMovingRight);
		}

		if (moveTime > 0.f) {
			if (!checkWallCollision(velocityX * deltaTime, 0.f, map)) {
				move(velocityX * deltaTime, 0, map);
				if (attacking)
				{
					attackAnimation->update(deltaTime, true);
					attackAnimation->applyToSprite(sprite, mIsMovingRight);
				}
				else if (abs(velocityX - 0.f) > 0.001f) {
					flyAnimation->update(deltaTime, true);
					flyAnimation->applyToSprite(sprite, mIsMovingRight);
				}
			}

			if (!checkWallCollision(0.f, velocityY * deltaTime, map)) {
				move(0, velocityY * deltaTime, map);
				if (attacking)
				{
					attackAnimation->update(deltaTime, true);
					attackAnimation->applyToSprite(sprite, mIsMovingRight);
				}
				else if (abs(velocityY - 0.f) > 0.001f) {
					flyAnimation->update(deltaTime, true);
					flyAnimation->applyToSprite(sprite, mIsMovingRight);
				}
			}
		}

	

		if (shooting) {
			shootAnimation->update(deltaTime, true);
			shootAnimation->applyToSprite(sprite, mIsMovingRight);
			return;
		}

		if (attacking)
		{
			attackAnimation->update(deltaTime, true);
			attackAnimation->applyToSprite(sprite, mIsMovingRight);
			return;
		}
		flyAnimation->update(deltaTime, true);
		flyAnimation->applyToSprite(sprite, mIsMovingRight);
	}
}

void Boss::move(float dx, float dy, Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		sprite.move(dx, dy);
		mPosition = sprite.getPosition();
	}
}


int Boss::checkWallCollision(float dx, float dy, Map* map) {
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

	if (bottomTileY >= map->getMapData().size()-1) {
		return -1;
	}

	// Check if the new position is outside the map
	if (rightTileX >= map->getMapData()[0].size()-1 || bottomTileY >= map->getMapData().size()-1) {
		//std::cout << "Check 1 -1" << std::endl;

		return -1; // Collision detected
	}

	if (tileX <= 1 || tileY <= 0 || tileY >= map->getMapData().size()-1) {
		//std::cout << tileX << " " << tileY << std::endl;
		//std::cout << "Check 2 -1" << std::endl;

		return -1;
	}

	std::vector<int> check(2);
	//std::cout << "Check 0" << std::endl;


	// Check if the new position collides with the wall (tile == '1')
	if (tileX >= 0 && tileX < map->getMapData()[0].size() && tileY >= 0 && tileY < map->getMapData().size()) {
		if (map->getMapData()[tileY][tileX] != '0' && map->getMapData()[tileY][tileX] != 'C' && map->getMapData()[tileY][rightTileX] != '2') {
			//std::cout << "Check 1" << std::endl;
			return 1; // Collision detected
		}
	}

	if (rightTileX >= 0 && rightTileX < map->getMapData()[0].size() && tileY >= 0 && tileY < map->getMapData().size()) {
		if (map->getMapData()[tileY][rightTileX] != '0' && map->getMapData()[tileY][rightTileX] != 'C' && map->getMapData()[tileY][rightTileX] != '2') {
			//std::cout << "Check 2" << std::endl;
			return 2; // Collision detected
		}
	}

	if (tileX >= 0 && tileX < map->getMapData()[0].size() && bottomTileY >= 0 && bottomTileY < map->getMapData().size()) {
		if (map->getMapData()[bottomTileY][tileX] != '0' && map->getMapData()[bottomTileY][tileX] != 'C' && map->getMapData()[tileY][rightTileX] != '2') {
			//std::cout << "Check 3" << std::endl;

			return 3; // Collision detected
		}
	}

	if (rightTileX >= 0 && rightTileX < map->getMapData()[0].size() && bottomTileY >= 0 && bottomTileY < map->getMapData().size()) {
		if (map->getMapData()[bottomTileY][rightTileX] != '0' && map->getMapData()[bottomTileY][rightTileX] != 'C' && map->getMapData()[tileY][rightTileX] != '2') {
			//std::cout << "Check 4" << std::endl;

			return 4; // Collision detected
		}
	}

	if (middleTileX >= 0 && middleTileX < map->getMapData()[0].size() && middleTileY >= 0 && middleTileY < map->getMapData().size()) {
		if (map->getMapData()[tileY][middleTileX] != '0' && map->getMapData()[tileY][middleTileX] != 'C' && map->getMapData()[tileY][rightTileX] != '2') {
			//std::cout << "Check 5" << std::endl;

			return 5; // Collision detected
		}
	}

	if (middleTileX >= 0 && middleTileX < map->getMapData()[0].size() && middleTileY >= 0 && middleTileY < map->getMapData().size()) {
		if (map->getMapData()[middleTileY][rightTileX] != '0' && map->getMapData()[middleTileY][rightTileX] != 'C' && map->getMapData()[tileY][rightTileX] != '2') {
			//std::cout << "Check 6" << std::endl;

			return 6; // Collision detected
		}
	}

	if (middleTileX >= 0 && middleTileX < map->getMapData()[0].size() && middleTileY >= 0 && middleTileY < map->getMapData().size()) {
		if (map->getMapData()[bottomTileY][middleTileX] != '0' && map->getMapData()[bottomTileY][middleTileX] != 'C' && map->getMapData()[tileY][rightTileX] != '2') {
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

void Boss::pushBack(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		if (mIsMovingRight) {
			if (checkWallCollision(-10.f, 0.f, map)) {
				velocityX = -velocityX;
			}
		}
		else {
			if (checkWallCollision(10.f, 0.f, map)) {
				velocityX = -velocityX;
			}
		}
	}
}

void Boss::dead(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		health = 0;
		Dead = true;
	}
}

void Boss::damaged(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		health -= 1;
		if (!mIsMovingRight) {
			sprite.move(-30.f, 0.f);
		}
		else {
			sprite.move(30.f, 0.f);
		}
		hit++;
		if (hit >= 10) {
			exhaust = true;
			hit = 0;
		}
		exhaustTime = 5.0f;
	}
}

void Boss::drawBounds(sf::RenderWindow& window)
{
	sf::FloatRect bounds = getBounds();
	sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
	rect.setPosition(bounds.left, bounds.top);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(1.f);
	window.draw(rect);
}


void Boss::circularShoot(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		sf::Vector2f position = sprite.getPosition();
		float angle = 0.f;
		for (int i = 0; i < 32; i++) {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 300.0f * cos(angle), 300.0f * sin(angle), position.x + getBounds().width / 2, position.y + getBounds().height / 2, mIsMovingRight);
			angle += 0.785398f/4.0f;
		}
		shooting = true;
		shootTime = 1.0f;
	}
}

void Boss::angularShoot(Map* map, sf::Vector2f player)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		attacking = true;
		attackTime = 1.0f;
		sf::Vector2f position = sprite.getPosition();
		float dx = player.x - position.x;
		float dy = player.y - position.y;
		float angle = atan2(dy, dx);
		if (!mIsMovingRight) angle += 3.14159f/2.0f;
		for (int i = 0; i < 8; i++) {
			map->enemyProjectiles.addProjectile(map->getProjectileTexture(), 300.0f * cos(angle), 300.0f * sin(angle), position.x + getBounds().width / 2, position.y + getBounds().height / 2, mIsMovingRight);
			map->enemyProjectiles.addProjectile(map->getProjectileTexture(), 300.0f * cos(angle)*1.5f, 300.0f * sin(angle)*1.5f, position.x + getBounds().width / 2+ 100.f, position.y + getBounds().height / 100.0f, mIsMovingRight);

			angle += 0.785398f/3.0f;
		}
	}
}

void Boss::normalAttack(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		attacking = true;
		sf::Vector2f position = sprite.getPosition();
		if (mIsMovingRight) {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 400.0f, 0.f, position.x + getBounds().width / 2, position.y + getBounds().height / 2, true);
		}
		else {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), -400.0f, 0.f, position.x + getBounds().width / 2, position.y + getBounds().height / 2, true);
		}
		attacking = true;
		attackTime = 1.0f;
	}
}

void Boss::groundShoot(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		shooting = true;
		shootTime = 1.0f;
		int leftRangeX = getBounds().left - 400;
		int rightRangeX = getBounds().left + getBounds().width + 400;
		for (int i = leftRangeX; i < rightRangeX; i += 80) {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 50.f, 300.0f, i, 100, mIsMovingRight);
		}
		for (int i = leftRangeX; i < rightRangeX; i += 80) {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 50.f, 300.0f, i, 50, mIsMovingRight);
		}
	}
}

void Boss::shootFromFeet(Map* map) {
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		shooting = true;
		shootTime = 1.0f;
		int bottomRangeY = getBounds().top + getBounds().height - 25.0f;
		int rightRangeX = getBounds().left + getBounds().width + 200;
		int leftRangeX = getBounds().left - 200;
		for (int i = leftRangeX; i < rightRangeX; i += 80) {
		    map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 100.f, 0.0f, i, getBounds().top, !mIsMovingRight);
		}

		for (int i = leftRangeX; i < rightRangeX; i += 80) {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 100.f, 0.0f, i, bottomRangeY, !mIsMovingRight);
		}

	}
}

void Boss::rainShoot(Map* map)
{
	if (activated) {
		if (health <= 0) {
			return;
		}
		if (exhaust) {
			return;
		}
		shooting = true;
		shootTime = 1.0f;
		int leftRangeX = getBounds().left - 400;
		int rightRangeX = getBounds().left + getBounds().width + 400;
		for (int i = leftRangeX; i < rightRangeX; i += 80) {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 0.f, 300.0f, i, 100, true);
		}
		for (int i = leftRangeX; i < rightRangeX; i += 80) {
			map->enemyProjectiles.addProjectile(map->getEnemyProjectileTexture(), 0.f, 300.0f, i, 50, true);
		}
			
	}
}




