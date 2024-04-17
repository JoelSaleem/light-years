#include "widgets/Widget.h"

namespace ly
{
    void Widget::NativeDraw(sf::RenderWindow &windowRef)
    {
        if (mIsVisible)
        {
            Draw(windowRef);
        }
    }

    bool Widget::HandleEvent(const sf::Event &event)
    {
        return false;
    }

    void Widget::SetWidgetRotation(float newRotation)
    {
        mWidgetTransform.setRotation(newRotation);
        RotationUpdated(newRotation);
    }

    void Widget::SetWidgetLocation(const sf::Vector2f &newLocation)
    {
        mWidgetTransform.setPosition(newLocation);
        LocationUpdated(newLocation);
    }

    void Widget::SetVisibility(bool newVisibility)
    {
        mIsVisible = newVisibility;
    }

    Widget::Widget() : mIsVisible{true}, mWidgetTransform{}
    {
    }

    void Widget::RotationUpdated(float newRotation)
    {
    }

    void Widget::LocationUpdated(const sf::Vector2f & newLocation)
    {
    }


    void Widget::Draw(sf::RenderWindow & windowRef)
    {
    }
}