#include "widgets/GameplayHUD.h"
#include <iostream>

namespace ly
{
    GameplayHUD::GameplayHUD()
        : mFrameRateText{"Frame Rate:"}
    {
        mFrameRateText.SetTextSize(30);
        mFrameRateText.SetVisibility(true);
    }

    void GameplayHUD::Draw(sf::RenderWindow &windowRef)
    {
        mFrameRateText.NativeDraw(windowRef);
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        int frameRate = int(1.f / deltaTime);
        std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
        mFrameRateText.SetString(frameRateStr);
    }
}
