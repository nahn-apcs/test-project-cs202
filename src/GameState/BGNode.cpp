#include <BGNode.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

BGNode::BGNode(const std::vector<sf::Sprite>& backgrounds) : mBackgrounds(backgrounds) {}

void BGNode::addBackground(const sf::Sprite& sprite) {
    mBackgrounds.push_back(sprite);
}


void BGNode::updateCurrent(sf::Time dt, CommandQueue&) {}

void BGNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& bg : mBackgrounds) {
        target.draw(bg, states);
    }
}
