#ifndef TEXT_NODE_HPP
#define TEXT_NODE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "SceneNode.hpp"


class TextNode : public SceneNode {
public:
    // Constructor: Takes the text and shadowText
    explicit TextNode(const sf::Text& text, const sf::Text& shadowText = sf::Text());

    // Override getCategory to assign a specific category
    virtual unsigned int getCategory() const override;

    // Methods for controlling the text
    void setScale(float scale);
    float getScale() const;
    virtual void updateTime(sf::Time dt);
    virtual float getElapsedTime() const;

private:
    // Draw the text and shadow
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    // UpdateCurrent does nothing now
    virtual void updateCurrent(sf::Time, CommandQueue&) override;

private:
    sf::Text mText;         // Main text
    sf::Text mShadowText;   // Shadow text
    float mScale;           // Current scale factor
    float mElapsedTime;     // Elapsed time
};

#endif // TEXT_NODE_HPP
