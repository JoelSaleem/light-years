#pragma once
#include <SFML/Graphics.hpp>
#include "widgets/Widget.h"
#include "framework/Core.h"

namespace ly
{
    class TextWidget : public Widget
    {
    public:
        TextWidget(const std::string &textStr,
                   const std::string &fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
                   unsigned int charSize = 10);

        void SetString(const std::string &newStr);
        void SetTextSize(unsigned int newSize);

    private:
        virtual void LocationUpdated(const sf::Vector2f &newLocation) override;
        virtual void RotationUpdated(float newRotation) override;
        virtual void Draw(sf::RenderWindow &ref) override;

        sf::Text mText;
        shared<sf::Font> mFont;
    };
}