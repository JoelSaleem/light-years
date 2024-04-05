#include "framework/World.h"
#include "Enemy/UFOStage.h"
#include "Enemy/UFO.h"
#include "framework/MathUtility.h"

namespace ly
{
    UFOStage::UFOStage(World *world)
        : GameStage{world},
          mSpawnInterval{4.f},
          mSpawnAmt{10},
          mCurrentSpawnAmt{0},
          mUFOSpeed{200.f}
    {
    }

    void UFOStage::StartStage()
    {
        mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
    }

    void UFOStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    sf::Vector2f UFOStage::GetRandomSpawnLoc() const
    {
        auto windowSize = GetWorld()->GetWindowSize();
        float spawnLeft = RandomRange(-1, 1);
        float spawnLocX = 0;
        if (spawnLeft < 0)
        {
            spawnLocX = windowSize.x + 100.f;
        }
        else
        {
            spawnLocX = -100.f;
        }

        float spawnLocY = RandomRange(0, windowSize.y);

        return sf::Vector2f{spawnLocX, spawnLocY};
    }

    void UFOStage::SpawnUFO()
    {
        auto spawnLoc = GetRandomSpawnLoc();
        auto windowSize = GetWorld()->GetWindowSize();
        sf::Vector2f center{windowSize.x / 2.f, windowSize.y / 2.f};
        sf::Vector2f spawnLocToCenter{center.x - spawnLoc.x, center.y - spawnLoc.y};
        Normalize(spawnLocToCenter);

        sf::Vector2f spawnVel = spawnLocToCenter * mUFOSpeed;

        weak<UFO> ufo = GetWorld()->SpawnActor<UFO>(spawnVel);
        ufo.lock()->SetActorLocation(spawnLoc);

        if (++mCurrentSpawnAmt == mSpawnAmt)
        {
            FinishStage();
        }
    }

}
