#include "TextNode.hpp"
#include "Command.hpp"

// Constructor
TextNode::TextNode(const sf::Text& text, const sf::Text& shadowText)
    : mText(text), mShadowText(shadowText), mScale(0.0f), mElapsedTime(0.0f) {
    mText.setScale(mScale, mScale);
    mShadowText.setScale(mScale, mScale);
}

// Override getCategory
unsigned int TextNode::getCategory() const {
    return Category::Text;
}


// Set the scale explicitly
void TextNode::setScale(float scale) {
    mScale = scale;
    mText.setScale(mScale, mScale);
    mShadowText.setScale(mScale, mScale);
}

// Get the current scale factor
float TextNode::getScale() const {
    return mScale;
}

// Update the elapsed time
void TextNode::updateTime(sf::Time dt) {
    mElapsedTime += dt.asSeconds();
}

// Get the elapsed time
float TextNode::getElapsedTime() const {
    return mElapsedTime;
}

void TextNode::updateCurrent(sf::Time dt, CommandQueue&) {}

// Draw the text and shadow
void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mShadowText, states); // Vẽ bóng chữ trước
    target.draw(mText, states);       // Vẽ chữ chính
}

