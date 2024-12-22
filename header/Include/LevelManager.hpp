#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include <vector>

class LevelManager {
public:

    static LevelManager& getInstance();
    void setLevels(int pos, int val);
    const int getLevels(int pos) const;
    void resetLevels();

private:
    LevelManager();
    ~LevelManager() = default;

    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    std::vector<int> mLevels;
    static LevelManager* sInstance;
};

#endif // LEVEL_MANAGER_HPP