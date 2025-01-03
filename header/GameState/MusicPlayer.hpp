#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <ResourceHolder.hpp>
#include <ResourceID.hpp>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


class MusicPlayer : private sf::NonCopyable
{
public:
	MusicPlayer();

	void						play(Music::ID theme);
	void						stop();

	void						setPaused(bool paused);
	void						setVolume(float volume);
	void						switchOnOff();
	bool						isOnMusic() const;
	

private:
	sf::Music							mMusic;
	std::map<Music::ID, std::string>	mFilenames;
	float								mVolume;
	bool								mOnMusic = 1;
};

#endif // MUSIC_PLAYER_HPP