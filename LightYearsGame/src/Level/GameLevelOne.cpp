#include "Level/GameLevelOne.h"
#include "framework/World.h"
#include "framework/TimerManager.h"
#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceship.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "gameplay/WaitStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "player/PlayerManager.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        : World{owningApp}
    {
        Player newPlayer = PlayerManager::Get().CreateNewPlayer();
        newPlayer.SpawnSpaceship(this);
    }

    void GameLevelOne::BeginPlay()
    {
    }

    void GameLevelOne::InitGameStages()
    {
        
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<VanguardStage>{new VanguardStage{this}});
        
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});
        
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<HexagonStage>{new HexagonStage{this}});
        
        AddStage(shared<WaitStage>{new WaitStage{this, 5.f}});
        AddStage(shared<UFOStage>{new UFOStage{this}});
    }
}
