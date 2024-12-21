#include <Application.hpp>
#include <MenuState.hpp>
#include <GuideState.hpp>
#include <LevelState.hpp>
#include <GameState.hpp>
#include <PauseState.hpp>
#include <WaitingState.hpp>
#include <TransitionState.hpp>
#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application(): mWindow(sf::VideoMode(1280, 640), "Input", sf::Style::Close), mTextures(), mFonts(), mStateStack(State::Context(mWindow, mTextures, mFonts)) {
    
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setVerticalSyncEnabled(true);

    //load Font
    mFonts.load(Fonts::Main, "Asset/Fonts/pixel.ttf");
	mFonts.load(Fonts::NameGame, "Asset/Fonts/NagasakiJapan.otf");


    //load Texture
    mTextures.load(Textures::ID::button, "Asset/Textures/button.png");
	mTextures.load(Textures::ID::MainMenuBG, "Asset/Textures/Menu/menubg.png");
	mTextures.load(Textures::ID::MainMenuBG_1, "Asset/Textures/Menu/menubg1.png");
	mTextures.load(Textures::ID::MainMenuBG_2, "Asset/Textures/Menu/menubg2.png");
	mTextures.load(Textures::ID::MainMenuBG_3, "Asset/Textures/Menu/menubg3.png");
	mTextures.load(Textures::ID::MainMenuClound_1, "Asset/Textures/Menu/cloud1.png");
	mTextures.load(Textures::ID::MainMenuClound_2, "Asset/Textures/Menu/cloud2.png");
	mTextures.load(Textures::ID::MainMenuClound_3, "Asset/Textures/Menu/cloud3.png");
	mTextures.load(Textures::ID::MainMenuClound_4, "Asset/Textures/Menu/cloud4.png");
	mTextures.load(Textures::ID::MainMenuClound_5, "Asset/Textures/Menu/cloud5.png");
	mTextures.load(Textures::ID::MainMenuClound_6, "Asset/Textures/Menu/cloud6.png");
	mTextures.load(Textures::ID::MainMenuClound_7, "Asset/Textures/Menu/cloud7.png");
	mTextures.load(Textures::ID::MainMenuClound_8, "Asset/Textures/Menu/cloud8.png");

	mTextures.load(Textures::ID::GuideBG, "Asset/Textures/Guide/guide.png");
	mTextures.load(Textures::ID::CloseGuide, "Asset/Textures/Guide/close_guide.png");

	mTextures.load(Textures::ID::LevelBG, "Asset/Textures/Level/level_bg.png");
	mTextures.load(Textures::ID::TestLevel, "Asset/Textures/Level/test_level.png");

	mTextures.load(Textures::ID::PauseBG, "Asset/Textures/Pause/PauseBG.png");
	mTextures.load(Textures::ID::PauseContinueButton, "Asset/Textures/Pause/ContinueButton.png");
	mTextures.load(Textures::ID::PauseRestartButton, "Asset/Textures/Pause/RestartButton.png");
	mTextures.load(Textures::ID::PauseMenuButton, "Asset/Textures/Pause/MenuButton.png");
	mTextures.load(Textures::ID::PauseSaveButton, "Asset/Textures/Pause/SaveButton.png");
	mTextures.load(Textures::ID::PauseSoundButton, "Asset/Textures/Pause/SoundButton.png");
	mTextures.load(Textures::ID::PauseMusicButton, "Asset/Textures/Pause/MusicButton.png");

	mTextures.load(Textures::ID::PauseButton, "Asset/Textures/Game/PauseButton.png");

	


    //register states
    registerStates();
    mStateStack.pushState(States::ID::Menu);


}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while(mWindow.isOpen()) {

        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while(timeSinceLastUpdate > TimePerFrame) {

            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty()) {
				mWindow.close();
			}
        }
        render();
    }
}

void Application::processInput() {
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<MenuState>(States::Menu);
	mStateStack.registerState<GuideState>(States::Guide);
	mStateStack.registerState<LevelState>(States::Level);
	mStateStack.registerState<GameState>(States::GameLevel1_1, 1, 1);
	mStateStack.registerState<GameState>(States::GameLevel1_2, 1, 2);
	mStateStack.registerState<GameState>(States::GameLevel2_1, 2, 1);
	mStateStack.registerState<GameState>(States::GameLevel2_2, 2, 2);
	mStateStack.registerState<GameState>(States::GameLevel3_1, 3, 1);
	mStateStack.registerState<GameState>(States::GameLevel3_2, 3, 2);
	mStateStack.registerState<GameState>(States::GameLevel4_1, 4, 1);
	mStateStack.registerState<GameState>(States::GameLevel4_2, 4, 2);
	mStateStack.registerState<GameState>(States::GameLevel5_1, 5, 1);
	mStateStack.registerState<GameState>(States::GameLevel5_2, 5, 2);

	mStateStack.registerState<PauseState>(States::Pause);
	mStateStack.registerState<WaitingState>(States::Waiting);
	mStateStack.registerState<TransitionState>(States::TransitionLevel1_1, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel1_1);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel1_2, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel1_2);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel2_1, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel2_1);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel2_2, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel2_2);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel3_1, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel3_1);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel3_2, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel3_2);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel4_1, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel4_1);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel4_2, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel4_2);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel5_1, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel5_1);
	});
	mStateStack.registerState<TransitionState>(States::TransitionLevel5_2, [this]() {
		this->mStateStack.popState();
		this->mStateStack.pushState(States::GameLevel5_2);
	});
	//mStateStack.registerState<TransitionState>(States::Transition);
	// mStateStack.registerState<TitleState>(States::Title);
	// mStateStack.registerState<GameState>(States::Game);
	// mStateStack.registerState<MultiplayerGameState>(States::HostGame, true);
	// mStateStack.registerState<MultiplayerGameState>(States::JoinGame, false);
	// mStateStack.registerState<PauseState>(States::Pause);
	// mStateStack.registerState<PauseState>(States::NetworkPause, true);
	// mStateStack.registerState<SettingsState>(States::Settings);
	// mStateStack.registerState<GameOverState>(States::GameOver, "Mission Failed!");
	// mStateStack.registerState<GameOverState>(States::MissionSuccess, "Mission Successful!");
}