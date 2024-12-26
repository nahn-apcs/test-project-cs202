#include "render.h"

//class Tile {
//	private:
//		TileType type;
//		sf::Sprite sprite;
//		sf::Texture texture;
//		sf::Vector2f position;
//		sf::Vector2f size;
//		sf::Vector2f scale;
//		sf::IntRect rect;
//		bool isCollidable;
//		bool isAnimated;
//		
//	public:
//		Tile();
//		Tile(sf::Sprite& s);
//		void draw(sf::RenderWindow& window);
//};
//
//class TileMap {
//	private:
//		std::vector<std::vector<Tile>> tiles;
//	public:
//		TileMap();
//		TileMap(std::vector<sf::Sprite> sprites);
//		void loadMap(std::string path);
//		void loadMap(std::vector<sf::Sprite> sprites);
//		void draw(sf::RenderWindow& window);
//		void update();
//		void setTile(int x, int y, TileType type);
//		
//};