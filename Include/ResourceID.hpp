#ifndef RESOURCE_ID_HPP
#define RESOURCE_ID_HPP

#include <ResourceHolder.hpp>

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class Shader;
	class SoundBuffer;
}

namespace Textures
{
    enum ID
    {
		//Menu
        button,
		MainMenuBG,
		MainMenuBG_1,
		MainMenuBG_2,
		MainMenuBG_3,
		MainMenuClound_1,
		MainMenuClound_2,
		MainMenuClound_3,
		MainMenuClound_4,
		MainMenuClound_5,
		MainMenuClound_6,
		MainMenuClound_7,
		MainMenuClound_8,
		MainMenuClound_9,

		//Guide
		GuideBG,
		CloseGuide,

		//Level
		LevelBG,
		TestLevel,
    };
}

namespace Fonts
{
	enum ID
	{
		Main,
		NameGame,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;




#endif // RESOURCE_ID_HPP