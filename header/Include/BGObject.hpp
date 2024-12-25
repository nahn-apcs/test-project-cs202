#ifndef BGOBJECT_HPP
#define BGOBJECT_HPP

#include <SceneNode.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class BGObject : public SceneNode {
public:
    explicit BGObject(const std::vector<sf::Sprite>& objects, const std::vector<float>& speeds);

    void addObject(const sf::Sprite& sprite, float speed);

private:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<sf::Sprite> mObjects; // Danh sách các sprite của đối tượng nền
    std::vector<float> mSpeeds;       // Tốc độ di chuyển của từng đối tượng
};

#endif // BGOBJECT_HPP
