#ifndef BGNODE_HPP
#define BGNODE_HPP

#include <SceneNode.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class BGNode : public SceneNode {
public:
    explicit BGNode(const std::vector<sf::Sprite>& backgrounds);


    void addBackground(const sf::Sprite& sprite);

private:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    std::vector<sf::Sprite> mBackgrounds;
};

#endif // BGNODE_HPP
