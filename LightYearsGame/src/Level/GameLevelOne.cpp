#include "Level/GameLevelOne.h"
#include "framework/World.h"
#include "framework/TimerManager.h"
#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceship.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "gameplay/WaitStage.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        : World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock().get()->SetActorLocation(sf::Vector2f{300, 490});
        testPlayerSpaceship.lock().get()->SetActorRotation(-90.f);
    }

    void GameLevelOne::BeginPlay()
    {
    }

    void GameLevelOne::InitGameStages()
    {
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
        AddStage(shared<WaitStage>{new WaitStage{this, 15.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
    }
}
