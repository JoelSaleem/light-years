#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;
    class GameplayHUD;
    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application *owningApp);

    private:
        weak<PlayerSpaceship> mPlayerSpaceship;
        weak<GameplayHUD> mGameplayHUD;

        virtual void BeginPlay() override;
        // virtual void Tick(float deltaTime);
        void TimerCallback_Test();
        TimerHandle timerHandle_Test;

        virtual void InitGameStages() override;
        void PlayerSpaceshipDestroyed(Actor *destoryedPlayerSpaceship);

        void GameOver();
    };
}