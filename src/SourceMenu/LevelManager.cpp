#include <LevelManager.hpp>



LevelManager::LevelManager() {
    for (int i = 0; i < 5; i++) {
        mLevels.push_back(0);
    }
    mLevels[0] = 1;
    mLevels[1] = 1;
    mLevels[2] = 1;
}



LevelManager& LevelManager::getInstance() {
    static LevelManager instance;
    return instance;
}


void LevelManager::setLevels(int pos, int val) {
    mLevels[pos] = val;
}

const int LevelManager::getLevels(int pos) const {
    return mLevels[pos];
}

void LevelManager::resetLevels() {
    for (int i = 0; i < 5; i++) {
        mLevels[i] = 0;
    }
}
