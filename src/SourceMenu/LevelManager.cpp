#include <LevelManager.hpp>


LevelManager::LevelManager() {
    for (int i = 0; i < 5; i++) {
        mLevels.push_back(0);
    }
    mLevels[0] = 1;

    curLevel = Level1;
    curCharacter = wukong;
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
    mLevels[0] = 1;
}

void LevelManager::setCurLevel(Level level) {
    curLevel = level;
}

LevelManager::Level LevelManager::getCurLevel() const {
    return curLevel;
}

void LevelManager::setCurCharacter(Character_1 character) {
    curCharacter = character;
}

LevelManager::Character_1 LevelManager::getCurCharacter() const {
    return curCharacter;
}


