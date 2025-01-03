#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

	Button::Button(State::Context context, Textures::ID TextureID, double _width, double _height, bool _open) : mCallback(), mSprite(context.textures->get(TextureID)), mText("", context.fonts->get(Fonts::Main), 20), mIsToggle(false), height(_height), width(_width), mOpen(_open)
	{
		changeTexture(Normal);

		sf::FloatRect bounds = mSprite.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Button::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}

	void Button::setText(const std::string& text)
	{
		mText.setString(text);
		centerOrigin(mText);
	}

	void Button::setText(const std::string& text, double height)
	{
		sf::FloatRect bounds = mSprite.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f + height);
		mText.setString(text);
		centerOrigin(mText);
	}

	void Button::setToggle(bool flag)
	{
		mIsToggle = flag;
	}


	bool Button::isSelectable() const
	{
		if (!mOpen) return false;
		return true;
	}

	void Button::select()
	{
		Component::select();

		changeTexture(Selected);
	}

	void Button::deselect()
	{
		Component::deselect();

		changeTexture(Normal);
	}

	void Button::activate()
	{
		Component::activate();

		// If we are toggle then we should show that the button is pressed and thus "toggled".
		if (mIsToggle)
			changeTexture(Pressed);

		if (mCallback)
			mCallback();

		// If we are not a toggle then deactivate the button since we are just momentarily activated.
		if (!mIsToggle)
			deactivate();

	}

	void Button::deactivate()
	{
		Component::deactivate();

		if (mIsToggle)
		{
			// Reset texture to right one depending on if we are selected or not.
			if (isSelected())
				changeTexture(Selected);
			else
				changeTexture(Normal);
		}
	}

	void Button::handleEvent(const sf::Event&)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
		target.draw(mText, states);
	}

	void Button::changeTexture(Type buttonType)
	{
		sf::IntRect textureRect(0, buttonType * height, width, height);
		mSprite.setTextureRect(textureRect);
		if (buttonType == Normal) {
			mSprite.setColor(sf::Color(255, 255, 255, 180));
		}
		else {
			mSprite.setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void Button::setOpen(bool flag)
	{
		mOpen = flag;
	}

}