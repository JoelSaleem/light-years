#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace ly
{
    GameStage::GameStage(World *world)
        : mWorld{world}, mStageFinished{false} {}

    void GameStage::StartStage()
    {
        LOG("stage started");
    }

    void GameStage::TickStage(float deltaTime)
    {
        LOG("tick stage");
    }

    void GameStage::FinishStage()
    {
        onStageFinished.Broadcast();
        mStageFinished = true;
        StageFinished();
    }

    void GameStage::StageFinished()
    {
        LOG("stage finished");
    }
}