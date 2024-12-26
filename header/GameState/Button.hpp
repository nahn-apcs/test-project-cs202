#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Component.hpp>
#include <ResourceID.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


class SoundPlayer;

namespace GUI
{

    class Button : public Component
    {
    public:
        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;

        enum Type
        {
            Selected,
            Normal,
            Pressed,
            ButtonCount
        };


    public:
        Button(State::Context context, Textures::ID textureID, double _width, double _height, bool _open = true);

        void					setCallback(Callback callback);
        void					setText(const std::string& text);
        void					setText(const std::string& text, double height);
        void					setToggle(bool flag);
        void                    setOpen(bool flag);

        virtual bool			isSelectable() const;
        virtual void			select();
        virtual void			deselect();

        virtual void			activate();
        virtual void			deactivate();

        virtual void			handleEvent(const sf::Event& event);



    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void					changeTexture(Type buttonType);


    private:
        Callback				mCallback;
        sf::Sprite				mSprite;
        sf::Text				mText;
        bool					mIsToggle;
        double                  width;
        double                  height;

        bool                    mOpen;
    };

}

#endif // BUTTON_HPP