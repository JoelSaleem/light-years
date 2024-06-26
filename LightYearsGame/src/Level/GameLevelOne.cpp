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
#include "widgets/GameplayHUD.h"

namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        : World{owningApp}
    {
    }

    void GameLevelOne::BeginPlay()
    {
        Player newPlayer = PlayerManager::Get().CreateNewPlayer();
        mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
        mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);

        mGameplayHUD = SpawnHUD<GameplayHUD>();
    }

    void GameLevelOne::PlayerSpaceshipDestroyed(Actor *destroyedPlayerSpaceship)
    {
        mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
        if (!mPlayerSpaceship.expired())
        {
            mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
            return;
        }

        GameOver();
    }

    void GameLevelOne::GameOver()
    {
        LOG("GAME OVER!!!!!!!!!!!!!!");
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
