//#include "tile.h"
//
//Tile::Tile() {
//	type = TileType::NONE;
//	position = sf::Vector2f(0, 0);
//	size = sf::Vector2f(constants::tile_size, constants::tile_size);
//	scale = sf::Vector2f(1, 1);
//	isCollidable = false;
//	isAnimated = false;
//}
//
//TileMap::TileMap() {
//	tiles = std::vector<std::vector<Tile>>();
//}
//
//void Tile::draw(sf::RenderWindow& window) {
//	sprite.setPosition(position);
//	sprite.setScale(scale);
//	window.draw(sprite);
//}
//
//void TileMap::draw(sf::RenderWindow& window) {
//	for (size_t i = 0; i < tiles.size(); ++i) {
//		for (size_t j = 0; j < tiles[i].size(); ++j) {
//			tiles[i][j].draw(window);
//		}
//	}
//}
//
//
//
//TileMap::TileMap(std::vector<sf::Sprite> sprites) {
//	tiles = std::vector<std::vector<Tile>>();
//	for (size_t i = 0; i < sprites.size(); ++i) {
//		std::vector<Tile> row;
//		for (size_t j = 0; j < sprites.size(); ++j) {
//			Tile tile(sprites[i]);
//			row.push_back(tile);
//		}
//		tiles.push_back(row);
//	}
//}