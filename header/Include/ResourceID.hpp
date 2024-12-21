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

		//WukongAsset1
		WukongStand1,
		WukongStand2,
		WukongStand3,
		WukongStand4,
		WukongJump1,
		WukongJump2,
		WukongJump3,
		WukongJump4,
		WukongRun1,
		WukongRun2,
		WukongRun3,
		WukongRun4,
		WukongAttack1,
		WukongAttack2,

		SmallWukongStand1,
		SmallWukongStand2,
		SmallWukongStand3,
		SmallWukongStand4,

		SmallWukongRun1,
		SmallWukongRun2,
		SmallWukongRun3,
		SmallWukongRun4,

		Bullet,
		Enemies,
		Bg1,
		Blocks,



    };
}

namespace Fonts
{
	enum ID
	{
		Main,
		NameGame,
		PixelNes,
	};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;




#endif // RESOURCE_ID_HPP