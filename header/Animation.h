#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
public:
    Animation(const std::vector<sf::Texture>& frames, float switchTime);

    void update(float deltaTime, bool loop = true);
    void applyToSprite(sf::Sprite& sprite, bool faceRight);

private:
    std::vector<sf::Texture> frames;  // A list of textures (the frames of the animation)
    float switchTime;  // Time interval to switch to the next frame
    float totalTime;   // Accumulated time for frame switching
    size_t currentFrame; // The current frame index
    int w, h;
};

#endif // ANIMATION_H
