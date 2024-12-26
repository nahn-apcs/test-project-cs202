#include <MusicPlayer.hpp>


MusicPlayer::MusicPlayer() : mMusic(), mFilenames(), mVolume(100.f) {
	mFilenames[Music::MenuTheme] = "../resources/Audio/menu.wav";
	mFilenames[Music::GameTheme] = "../resources/Audio/Background.wav";
	mFilenames[Music::WinningTheme] = "../resources/Audio/win.wav";
	mFilenames[Music::LevelCompleteTheme] = "../resources/Audio/victory.wav";
	mFilenames[Music::GameOverTheme] = "../resources/Audio/game_over.wav";
}

void MusicPlayer::play(Music::ID theme) {
	std::string filename = mFilenames[theme];

	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void MusicPlayer::stop() {
	mMusic.stop();
}

void MusicPlayer::setVolume(float volume) {
	mVolume = volume;
	mMusic.setVolume(mVolume);
}

void MusicPlayer::setPaused(bool paused) {
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
}