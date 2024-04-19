#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"
#include <iostream>

namespace ly
{
    TextWidget::TextWidget(
        const std::string &textStr,
        const std::string &fontPath,
        unsigned int charSize)
        : mFont{AssetManager::Get().LoadFont(fontPath)},
          mText{textStr, *(mFont.get()), charSize}
    {
        mText.setPosition({100, 100});
        mText.setColor(sf::Color::Blue);
        mText.setFillColor(sf::Color::Blue);
        auto x = mText.getPosition();

        std::cout << x.x << " " << x.y << std::endl;
        std::cout << mText.getString().toAnsiString() << std::endl;
    }

    void TextWidget::SetString(const std::string &newStr)
    {
        mText.setString(newStr);
    }

    void TextWidget::SetTextSize(unsigned int newSize)
    {
        mText.setCharacterSize(newSize);
    }

    void TextWidget::LocationUpdated(const sf::Vector2f &newLocation)
    {
        mText.setPosition(newLocation);
    }

    void TextWidget::RotationUpdated(float newRotation)
    {
        mText.setRotation(newRotation);
    }

    void TextWidget::Draw(sf::RenderWindow &ref)
    {
        ref.draw(mText);
    }
}
