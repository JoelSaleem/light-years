#pragma once

#include <SFML/Graphics.hpp>
#include "gameplay/GameStage.h"
#include "framework/TimerManager.h"
#include "framework/TimerManager.h"

namespace ly
{
    class UFOStage : public GameStage
    {

    public:
        UFOStage(World *world);

        virtual void StartStage() override;

    private:
        virtual void StageFinished() override;
        sf::Vector2f GetRandomSpawnLoc() const;;
        void SpawnUFO();
        
        int mSpawnAmt;
        float mSpawnInterval;
        int mCurrentSpawnAmt;
        float mUFOSpeed;

        TimerHandle mSpawnTimer;
    };
}