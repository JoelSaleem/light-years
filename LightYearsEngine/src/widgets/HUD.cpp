#include "widgets/HUD.h"
#include "HUD.h"

namespace ly
{
    HUD::HUD() : mAlreadyInit{false}
    {
    }

    void HUD::Init(sf::RenderWindow &windowRef)
    {
    }

    void HUD::Draw(sf::RenderWindow &windowRef)
    {
    }

    void HUD::NativeInit(sf::RenderWindow &windowRef)
    {
        if (!mAlreadyInit)
        {
            mAlreadyInit = true;
            Init(windowRef);
        }
    }

    bool HUD::HandleEvent(const sf::Event &event)
    {
        return false;
    }
}