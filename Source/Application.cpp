#include <Application.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application(): mWindow(sf::VideoMode(1280, 640), "Input", sf::Style::Close), mTextures(), mFonts(), mStateStack(State::Context(mWindow, mTextures, mFonts)) {
    
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setVerticalSyncEnabled(true);

    //load Font
    mFonts.load(Fonts::Main, "Asset/Fonts/Sansation.ttf");


    //load Texture
    mTextures.load(Textures::button, "Asset/Textures/button.png");


    //register states
    // registerStates();
    // mStateStack.pushState(States::Title);


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
			// if (mStateStack.isEmpty())
			// 	mWindow.close();
        }
        render();
    }
}

void Application::processInput() {
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		//mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::update(sf::Time dt)
{
	//mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear();

	//mStateStack.draw();

	mWindow.setView(mWindow.getDefaultView());

	mWindow.display();
}

void Application::registerStates()
{
	// mStateStack.registerState<TitleState>(States::Title);
	// mStateStack.registerState<MenuState>(States::Menu);
	// mStateStack.registerState<GameState>(States::Game);
	// mStateStack.registerState<MultiplayerGameState>(States::HostGame, true);
	// mStateStack.registerState<MultiplayerGameState>(States::JoinGame, false);
	// mStateStack.registerState<PauseState>(States::Pause);
	// mStateStack.registerState<PauseState>(States::NetworkPause, true);
	// mStateStack.registerState<SettingsState>(States::Settings);
	// mStateStack.registerState<GameOverState>(States::GameOver, "Mission Failed!");
	// mStateStack.registerState<GameOverState>(States::MissionSuccess, "Mission Successful!");
}