#include <Application.hpp>
#include <MenuState.hpp>
#include <GuideState.hpp>
#include <LevelState.hpp>
#include <GameState.hpp>
#include <PauseState.hpp>
#include <WaitingState.hpp>
#include <TransitionState.hpp>
#include <LevelManager.hpp>
#include <LevelCompleteState.hpp>
#include <WinningState.hpp>
#include <GameOverState.hpp>
#include <SettingState.hpp>
#include <iostream>

const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application() : mWindow(sf::VideoMode(1280, 640), "Input", sf::Style::Close), mTextures(), mFonts(), mMusic(), mAudio(), mStateStack(State::Context(mWindow, mTextures, mFonts, mMusic, mAudio)) {

    mWindow.setKeyRepeatEnabled(false);
    mWindow.setVerticalSyncEnabled(true);
	mFonts.load(Fonts::PixelNes, "../resources/font/Pixel_NES.otf");

	

	
	mTextures.load(Textures::ID::WukongStand1, "../resources/wukong16bit/stand wk_sprite_1.png");
	mTextures.load(Textures::ID::WukongStand2, "../resources/wukong16bit/stand wk_sprite_2.png");
	mTextures.load(Textures::ID::WukongStand3, "../resources/wukong16bit/stand wk_sprite_3.png");
	mTextures.load(Textures::ID::WukongStand4, "../resources/wukong16bit/stand wk_sprite_4.png");
	mTextures.load(Textures::ID::WukongJump1, "../resources/wukong16bit/jumpwk_sprite_1.png");
	mTextures.load(Textures::ID::WukongJump2, "../resources/wukong16bit/jumpwk_sprite_2.png");
	mTextures.load(Textures::ID::WukongJump3, "../resources/wukong16bit/jumpwk_sprite_3.png");
	mTextures.load(Textures::ID::WukongJump4, "../resources/wukong16bit/jumpwk_sprite_4.png");
	mTextures.load(Textures::ID::WukongRun1, "../resources/wukong16bit/run wk_sprite_1.png");
	mTextures.load(Textures::ID::WukongRun2, "../resources/wukong16bit/run wk_sprite_2.png");
	mTextures.load(Textures::ID::WukongRun3, "../resources/wukong16bit/run wk_sprite_3.png");
	mTextures.load(Textures::ID::WukongRun4, "../resources/wukong16bit/run wk_sprite_4.png");
	mTextures.load(Textures::ID::WukongAttack1, "../resources/wukong16bit/atk wk 3_sprite_2.png");
	mTextures.load(Textures::ID::WukongAttack2, "../resources/wukong16bit/atk wk 3_sprite_3.png");

	mTextures.load(Textures::ID::SmallWukongStand1, "../resources/wukong16bit/stand_sprite_1.png");
	mTextures.load(Textures::ID::SmallWukongStand2, "../resources/wukong16bit/stand_sprite_2.png");
	mTextures.load(Textures::ID::SmallWukongStand3, "../resources/wukong16bit/stand_sprite_3.png");
	mTextures.load(Textures::ID::SmallWukongStand4, "../resources/wukong16bit/stand_sprite_4.png");

	mTextures.load(Textures::ID::SmallWukongRun1, "../resources/wukong16bit/run_sprite_1.png");
	mTextures.load(Textures::ID::SmallWukongRun2, "../resources/wukong16bit/run_sprite_2.png");
	mTextures.load(Textures::ID::SmallWukongRun3, "../resources/wukong16bit/run_sprite_3.png");
	mTextures.load(Textures::ID::SmallWukongRun4, "../resources/wukong16bit/run_sprite_4.png");

	mTextures.load(Textures::ID::DeadWukong1, "../resources/wukong16bit/dead_sprite_1.png");
	mTextures.load(Textures::ID::DeadWukong2, "../resources/wukong16bit/dead_sprite_2.png");
	mTextures.load(Textures::ID::DeadWukong3, "../resources/wukong16bit/dead_sprite_3.png");
	mTextures.load(Textures::ID::DeadWukong4, "../resources/wukong16bit/dead_sprite_4.png");
	mTextures.load(Textures::ID::DeadWukong5, "../resources/wukong16bit/dead_sprite_5.png");
	mTextures.load(Textures::ID::DeadWukong6, "../resources/wukong16bit/dead_sprite_6.png");
	mTextures.load(Textures::ID::DeadWukong7, "../resources/wukong16bit/dead_sprite_7.png");
	mTextures.load(Textures::ID::DeadWukong8, "../resources/wukong16bit/dead_sprite_8.png");
	mTextures.load(Textures::ID::DeadWukong9, "../resources/wukong16bit/dead_sprite_9.png");

	mTextures.load(Textures::ID::WukongHurt1, "../resources/wukong16bit/hit wk_sprite_1.png");
	mTextures.load(Textures::ID::WukongHurt2, "../resources/wukong16bit/hit wk_sprite_2.png");
	mTextures.load(Textures::ID::WukongHurt3, "../resources/wukong16bit/hit wk_sprite_3.png");

	mTextures.load(Textures::ID::SmallWukongHurt1, "../resources/wukong16bit/hit_sprite_1.png");
	mTextures.load(Textures::ID::SmallWukongHurt2, "../resources/wukong16bit/hit_sprite_2.png");
	mTextures.load(Textures::ID::SmallWukongHurt3, "../resources/wukong16bit/hit_sprite_3.png");

	mTextures.load(Textures::ID::SecondWukongRun1, "../resources/sprite_sheet/wukong/run_sprite_1.png");
	mTextures.load(Textures::ID::SecondWukongRun2, "../resources/sprite_sheet/wukong/run_sprite_2.png");
	mTextures.load(Textures::ID::SecondWukongRun3, "../resources/sprite_sheet/wukong/run_sprite_3.png");
	mTextures.load(Textures::ID::SecondWukongRun4, "../resources/sprite_sheet/wukong/run_sprite_4.png");
	mTextures.load(Textures::ID::SecondWukongRun5, "../resources/sprite_sheet/wukong/run_sprite_5.png");
	mTextures.load(Textures::ID::SecondWukongRun6, "../resources/sprite_sheet/wukong/run_sprite_6.png");
	mTextures.load(Textures::ID::SecondWukongRun7, "../resources/sprite_sheet/wukong/run_sprite_7.png");
	mTextures.load(Textures::ID::SecondWukongRun8, "../resources/sprite_sheet/wukong/run_sprite_8.png");

	mTextures.load(Textures::ID::SecondWukongStand1, "../resources/sprite_sheet/wukong/idle_sprite_1.png");
	mTextures.load(Textures::ID::SecondWukongStand2, "../resources/sprite_sheet/wukong/idle_sprite_2.png");
	mTextures.load(Textures::ID::SecondWukongStand3, "../resources/sprite_sheet/wukong/idle_sprite_3.png");
	mTextures.load(Textures::ID::SecondWukongStand4, "../resources/sprite_sheet/wukong/idle_sprite_4.png");
	mTextures.load(Textures::ID::SecondWukongStand5, "../resources/sprite_sheet/wukong/idle_sprite_5.png");

	mTextures.load(Textures::ID::SecondWukongAttack1, "../resources/sprite_sheet/wukong/attack_sprite_1.png");
	mTextures.load(Textures::ID::SecondWukongAttack2, "../resources/sprite_sheet/wukong/attack_sprite_2.png");
	mTextures.load(Textures::ID::SecondWukongAttack3, "../resources/sprite_sheet/wukong/attack_sprite_3.png");
	mTextures.load(Textures::ID::SecondWukongAttack4, "../resources/sprite_sheet/wukong/attack_sprite_4.png");
	mTextures.load(Textures::ID::SecondWukongAttack5, "../resources/sprite_sheet/wukong/attack_sprite_5.png");
	mTextures.load(Textures::ID::SecondWukongAttack6, "../resources/sprite_sheet/wukong/attack_sprite_6.png");
	mTextures.load(Textures::ID::SecondWukongAttack7, "../resources/sprite_sheet/wukong/attack_sprite_7.png");

	mTextures.load(Textures::ID::SecondWukongDead1, "../resources/sprite_sheet/wukong/dead_sprite_1.png");
	mTextures.load(Textures::ID::SecondWukongDead2, "../resources/sprite_sheet/wukong/dead_sprite_2.png");
	mTextures.load(Textures::ID::SecondWukongDead3, "../resources/sprite_sheet/wukong/dead_sprite_3.png");
	mTextures.load(Textures::ID::SecondWukongDead4, "../resources/sprite_sheet/wukong/dead_sprite_4.png");
	mTextures.load(Textures::ID::SecondWukongDead5, "../resources/sprite_sheet/wukong/dead_sprite_5.png");
	mTextures.load(Textures::ID::SecondWukongDead6, "../resources/sprite_sheet/wukong/dead_sprite_6.png");
	mTextures.load(Textures::ID::SecondWukongDead7, "../resources/sprite_sheet/wukong/dead_sprite_7.png");

	mTextures.load(Textures::ID::SecondWukongHurt1, "../resources/sprite_sheet/wukong/hit_sprite_1.png");
	mTextures.load(Textures::ID::SecondWukongHurt2, "../resources/sprite_sheet/wukong/hit_sprite_2.png");
	mTextures.load(Textures::ID::SecondWukongHurt3, "../resources/sprite_sheet/wukong/hit_sprite_3.png");




	mTextures.load(Textures::ID::BossAttack1, "../resources/boss minotaur/main/boss_attacking_1_fit.png");
	mTextures.load(Textures::ID::BossAttack2, "../resources/boss minotaur/main/boss_attacking_2_fit.png");
	mTextures.load(Textures::ID::BossAttack3, "../resources/boss minotaur/main/boss_attacking_3_fit.png");
	mTextures.load(Textures::ID::BossDead1, "../resources/boss minotaur/main/boss_dead_1.png");
	mTextures.load(Textures::ID::BossDead2, "../resources/boss minotaur/main/boss_dead_2.png");
	mTextures.load(Textures::ID::BossDead3, "../resources/boss minotaur/main/boss_dead_3.png");
	mTextures.load(Textures::ID::BossDead4, "../resources/boss minotaur/main/boss_dead_4.png");
	mTextures.load(Textures::ID::BossDead5, "../resources/boss minotaur/main/boss_dead_5.png");
	mTextures.load(Textures::ID::BossDead6, "../resources/boss minotaur/main/boss_dead_6.png");
	mTextures.load(Textures::ID::BossDead7, "../resources/boss minotaur/main/boss_dead_7.png");
	mTextures.load(Textures::ID::BossFly1, "../resources/boss minotaur/main/boss_flying_1.png");
	mTextures.load(Textures::ID::BossFly2, "../resources/boss minotaur/main/boss_flying_2.png");
	mTextures.load(Textures::ID::BossFly3, "../resources/boss minotaur/main/boss_flying_3.png");
	mTextures.load(Textures::ID::BossFly4, "../resources/boss minotaur/main/boss_flying_4.png");

	mTextures.load(Textures::ID::BossShoot1, "../resources/boss minotaur/main/boss_shooting_1.png");
	mTextures.load(Textures::ID::BossShoot2, "../resources/boss minotaur/main/boss_shooting_2.png");

	mTextures.load(Textures::ID::BossExhausted1, "../resources/boss minotaur/main/boss_exhausted_1.png");
	mTextures.load(Textures::ID::BossExhausted2, "../resources/boss minotaur/main/boss_exhausted_2.png");

	mTextures.load(Textures::ID::BossBullet, "../resources/boss_bullet.png");

  mTextures.load(Textures::ID::Bg2, "../resources/Level2/bg.png");
  mTextures.load(Textures::ID::Blocks2, "../resources/Level2/blocks.png");
  mTextures.load(Textures::ID::Bg3, "../resources/Level3/bg.png");
  mTextures.load(Textures::ID::Blocks3, "../resources/Level3/blocks.png");
	
	mTextures.load(Textures::ID::Bullet, "../resources/bullet1_strip.png");
	mTextures.load(Textures::ID::Enemies, "../resources/Run-sheet.png");
	mTextures.load(Textures::ID::Bg1, "../resources/Level1/bg.png");
	mTextures.load(Textures::ID::Blocks, "../resources/Level1/blocks.png");
	

	//load Font
	mFonts.load(Fonts::Main, "../resources/Asset/Fonts/pixel.ttf");
	mFonts.load(Fonts::NameGame, "../resources/Asset/Fonts/NagasakiJapan.otf");

	//load Texture
	mTextures.load(Textures::ID::button, "../resources/Asset/Textures/button.png");
	mTextures.load(Textures::ID::MainMenuBG, "../resources/Asset/Textures/Menu/menubg.png");
	mTextures.load(Textures::ID::MainMenuBG_1, "../resources/Asset/Textures/Menu/menubg1.png");
	mTextures.load(Textures::ID::MainMenuBG_2, "../resources/Asset/Textures/Menu/menubg2.png");
	mTextures.load(Textures::ID::MainMenuBG_3, "../resources/Asset/Textures/Menu/menubg3.png");
	mTextures.load(Textures::ID::MainMenuClound_1, "../resources/Asset/Textures/Menu/cloud1.png");
	mTextures.load(Textures::ID::MainMenuClound_2, "../resources/Asset/Textures/Menu/cloud2.png");
	mTextures.load(Textures::ID::MainMenuClound_3, "../resources/Asset/Textures/Menu/cloud3.png");
	mTextures.load(Textures::ID::MainMenuClound_4, "../resources/Asset/Textures/Menu/cloud4.png");
	mTextures.load(Textures::ID::MainMenuClound_5, "../resources/Asset/Textures/Menu/cloud5.png");
	mTextures.load(Textures::ID::MainMenuClound_6, "../resources/Asset/Textures/Menu/cloud6.png");
	mTextures.load(Textures::ID::MainMenuClound_7, "../resources/Asset/Textures/Menu/cloud7.png");
	mTextures.load(Textures::ID::MainMenuClound_8, "../resources/Asset/Textures/Menu/cloud8.png");

	mTextures.load(Textures::ID::GuideBG, "../resources/Asset/Textures/Guide/guide.png");
	mTextures.load(Textures::ID::CloseGuide, "../resources/Asset/Textures/Guide/close_guide.png");

	mTextures.load(Textures::ID::LevelBG, "../resources/Asset/Textures/Level/level_bg.png");
	mTextures.load(Textures::ID::LevelBackButton, "../resources/Asset/Textures/Level/BackButton.png");
	mTextures.load(Textures::ID::LevelLock, "../resources/Asset/Textures/Level/Lock.png");
	mTextures.load(Textures::ID::LevelMap_1, "../resources/Asset/Textures/Level/Map1.png");
	mTextures.load(Textures::ID::LevelMap_2, "../resources/Asset/Textures/Level/Map2.png");
	mTextures.load(Textures::ID::LevelMap_3, "../resources/Asset/Textures/Level/Map3.png");
	mTextures.load(Textures::ID::LevelMap_4, "../resources/Asset/Textures/Level/Map4.png");
	mTextures.load(Textures::ID::LevelMap_5, "../resources/Asset/Textures/Level/Map5.png");
	mTextures.load(Textures::ID::LevelPointer1, "../resources/Asset/Textures/Level/Pointer1.png");
	mTextures.load(Textures::ID::LevelPointer2, "../resources/Asset/Textures/Level/Pointer2.png");
	mTextures.load(Textures::ID::LevelPointer3, "../resources/Asset/Textures/Level/Pointer3.png");
	mTextures.load(Textures::ID::LevelPointer4, "../resources/Asset/Textures/Level/Pointer4.png");
	mTextures.load(Textures::ID::LevelPointer5, "../resources/Asset/Textures/Level/Pointer5.png");

	mTextures.load(Textures::ID::PauseBG, "../resources/Asset/Textures/Pause/PauseBG.png");
	mTextures.load(Textures::ID::PauseContinueButton, "../resources/Asset/Textures/Pause/ContinueButton.png");
	mTextures.load(Textures::ID::PauseRestartButton, "../resources/Asset/Textures/Pause/RestartButton.png");
	mTextures.load(Textures::ID::PauseMenuButton, "../resources/Asset/Textures/Pause/MenuButton.png");
	mTextures.load(Textures::ID::PauseSaveButton, "../resources/Asset/Textures/Pause/SaveButton.png");
	mTextures.load(Textures::ID::PauseSoundButton, "../resources/Asset/Textures/Pause/SoundButton.png");
	mTextures.load(Textures::ID::PauseMusicButton, "../resources/Asset/Textures/Pause/MusicButton.png");

	mTextures.load(Textures::ID::PauseButton, "../resources/Asset/Textures/Game/PauseButton.png");

	mTextures.load(Textures::ID::LevelCompleteBG, "../resources/Asset/Textures/CompleteLevel/BackGround.png");
	mTextures.load(Textures::ID::LevelCompleteNextButton, "../resources/Asset/Textures/CompleteLevel/NextButton.png");
	mTextures.load(Textures::ID::LevelCompleteBackButton, "../resources/Asset/Textures/CompleteLevel/BackButton.png");

	mTextures.load(Textures::ID::WinningBG, "../resources/Asset/Textures/Winning/WinningBG.png");
	mTextures.load(Textures::ID::WinningRestartButton, "../resources/Asset/Textures/Winning/RestartButton.png");
	mTextures.load(Textures::ID::WinningBoard, "../resources/Asset/Textures/Winning/Board.png");

	mTextures.load(Textures::ID::GameOverBoard, "../resources/Asset/Textures/GameOver/Board.png");
	mTextures.load(Textures::ID::GameOverMenuButton, "../resources/Asset/Textures/GameOver/MenuButton.png");
	mTextures.load(Textures::ID::GameOverRestartButton, "../resources/Asset/Textures/GameOver/RestartButton.png");

	mTextures.load(Textures::ID::SettingBoard, "../resources/Asset/Textures/Setting/Board.png");
	mTextures.load(Textures::ID::SettingSoundButton, "../resources/Asset/Textures/Setting/SoundButton.png");
	mTextures.load(Textures::ID::SettingMusicButton, "../resources/Asset/Textures/Setting/MusicButton.png");
	mTextures.load(Textures::ID::SettingCloseButton, "../resources/Asset/Textures/Setting/CloseButton.png");


	//set volume
	mMusic.setVolume(25.f);

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
	mStateStack.registerState<GameState>(States::Game);

	mStateStack.registerState<PauseState>(States::Pause);

	mStateStack.registerState<LevelCompleteState>(States::LevelComplete);

	mStateStack.registerState<GameOverState>(States::GameOver);

	mStateStack.registerState<WinningState>(States::Winning);

	mStateStack.registerState<WaitingState>(States::Waiting);

	mStateStack.registerState<TransitionState>(States::TransitionMenu, TransitionState::Menu);
	mStateStack.registerState<TransitionState>(States::TransitionGame, TransitionState::Game);
	mStateStack.registerState<TransitionState>(States::TransitionWinning, TransitionState::Winning);
	mStateStack.registerState<TransitionState>(States::TransitionGame_2, TransitionState::Game, 2);
	mStateStack.registerState<SettingState>(States::Setting);
}