#include "Enemy/HexagonStage.h"
#include "Enemy/Hexagon.h"
#include "framework/World.h"

namespace ly
{

    HexagonStage::HexagonStage(World *world)
        : GameStage{world},
          mSpanwInterval{5.f},
          mSideSpawnOffset{80.f},
          mSpawnGroupAmt{5},
          mCurrentSpawnCount{0},
          mMidSpawnLoc{world->GetWindowSize().x / 2.f, -100.f},
          mRightSpawnLoc{world->GetWindowSize().x / 2.f + mSideSpawnOffset, -100.f - mSideSpawnOffset},
          mLeftSpawnLoc{world->GetWindowSize().x / 2.f - mSideSpawnOffset, -100.f - mSideSpawnOffset}
    {
    }

    void HexagonStage::StartStage()
    {
        mSpawnTimer = TimerManager::Get()
                          .SetTimer(
                              GetWeakRef(),
                              &HexagonStage::SpawnHexagon,
                              mSpawnGroupAmt,
                              true);
    }

    void HexagonStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimer);
    }

    void HexagonStage::SpawnHexagon()
    {
        weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(mMidSpawnLoc);

        newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(mLeftSpawnLoc);

        newHexagon = GetWorld()->SpawnActor<Hexagon>();
        newHexagon.lock()->SetActorLocation(mRightSpawnLoc);

        if (++mCurrentSpawnCount == mSpawnGroupAmt)
        {
            FinishStage();
        }
    }
}
