#include "framework/World.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/Vanguard.h"

namespace ly
{
    VanguardStage::VanguardStage(World *world)
        : GameStage{world},
          mSpawnInterval{2.f},
          mSwitchInterval{5.f},
          mSpawnDistanceToEdge{100.f},
          mLeftSpawnLoc{0.0f, 0.0f},
          mRightSpawnLoc{0.0f, 0.0f},
          mSpawnLoc{0.0f, 0.0f},
          mRowsToSpawn{2},
          mCurrentRowVanguardCount{0},
          mVanguardsPerRow{5},
          mRowSpawnCount{0}
    {
    }

    void VanguardStage::StartStage()
    {
        auto windowSize = GetWorld()->GetWindowSize();

        mLeftSpawnLoc = sf::Vector2f{mSpawnDistanceToEdge, -100.f};
        mRightSpawnLoc = sf::Vector2f{windowSize.x - mSpawnDistanceToEdge, -100.f};

        SwitchRow();
    }

    void VanguardStage::StageFinished()
    {
        TimerManager::Get().ClearTimer(mSpawnTimerHandle);
        TimerManager::Get().ClearTimer(mSwitchTimerHandle);
    }

    void VanguardStage::SpawnVanguard()
    {
        weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
        newVanguard.lock()->SetActorLocation(mSpawnLoc);

        ++mCurrentRowVanguardCount;
        if (mCurrentRowVanguardCount == mVanguardsPerRow)
        {
            TimerManager::Get().ClearTimer(mSpawnTimerHandle);
            mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
            mCurrentRowVanguardCount = 0;
        }
    }

    void VanguardStage::SwitchRow()
    {
        if (mRowSpawnCount == mRowsToSpawn)
        {
            FinishStage();
            return;
        }

        if (mSpawnLoc == mLeftSpawnLoc)
        {
            mSpawnLoc = mRightSpawnLoc;
        }
        else
        {
            mSpawnLoc = mLeftSpawnLoc;
        }

        mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

        ++mRowSpawnCount;
    }
}
