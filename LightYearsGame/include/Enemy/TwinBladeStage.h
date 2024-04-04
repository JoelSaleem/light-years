#pragma once

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"

namespace ly
{
    class TwinBladeStage : public GameStage
    {

    public:
        TwinBladeStage(World *world);

        virtual void StartStage() override;

    private:
        float mSpawnInterval;
        float mSwitchInterval;
        float mSpawnDistanceToCenter;

        sf::Vector2f mLeftSpawnLoc;
        sf::Vector2f mRightSpawnLoc;
        sf::Vector2f mSpawnLoc;

        TimerHandle mSpawnTimerHandle;

        int mSpawnAmt;
        int mCurrentSpawnCount;

        virtual void StageFinished() override;
        void SpawnTwinBlade();
    };
}