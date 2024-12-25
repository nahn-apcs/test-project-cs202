#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include <vector>

class LevelManager {
public:

    enum Level {
        Level1,
        Level2,
        Level3,
        Level4,
        Level5
    };

    enum Character {
        wukong,
        pig
    };

    static LevelManager& getInstance();
    void setLevels(int pos, int val);
    const int getLevels(int pos) const;
    void resetLevels();
    void setCurLevel(Level level);
    Level getCurLevel() const;
    void setCurCharacter(Character character);
    Character getCurCharacter() const;

private:
    LevelManager();
    ~LevelManager() = default;

    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    std::vector<int> mLevels;
    Level curLevel;
    Character curCharacter;
    static LevelManager* sInstance;
};


#endif // LEVEL_MANAGER_HPP