
#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

typedef enum Screen { MENU, LEVEL1, LEVEL2, LEVEL3 } Screen;
typedef enum Interact { REST, CREATE, INSERT, DELETE, SEARCH, FILEINTER };
typedef enum TileType {
	GROUND,
	NONE
} TileType;


namespace constants {

	constexpr int scene_width = 1366;
	constexpr int scene_height = 640;
	constexpr int frames_per_second = 60;

	constexpr int tile_size = 32;
}

#endif  // CONSTANTS_HPP_
