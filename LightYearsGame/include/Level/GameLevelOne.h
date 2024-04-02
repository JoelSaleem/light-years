#pragma once
#include "framework/World.h"

namespace ly
{
    class PlayerSpaceship;
    class GameLevelOne : public World
    {
    public:
        GameLevelOne(Application *owningApp);
    
    private:
        weak<PlayerSpaceship> testPlayerSpaceship;
        virtual void BeginPlay() override;
        // virtual void Tick(float deltaTime);
        void TimerCallback_Test();
    };
}