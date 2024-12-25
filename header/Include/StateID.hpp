#ifndef STATE_ID_HPP
#define STATE_ID_HPP

namespace States
{
    enum ID
    {
        None,
        Menu,
        Guide,
        Level,
        Game,
        Pause,
        Waiting,
        TransitionMenu,
        TransitionGame,
        TransitionGame_2,
        TransitionWinning,
        LevelComplete,
        Winning,
        GameOver,
        Setting,
    };
}

#endif // STATE_ID_HPP