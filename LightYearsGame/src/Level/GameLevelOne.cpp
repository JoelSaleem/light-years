#include "Level/GameLevelOne.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "spaceship/Spaceship.h"
#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceship.h"


namespace ly
{
    GameLevelOne::GameLevelOne(Application *owningApp)
        : World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock().get()->SetActorLocation(sf::Vector2f{300, 490});
        testPlayerSpaceship.lock().get()->SetActorRotation(-90.f);

        weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
        testSpaceship.lock().get()->SetActorLocation(sf::Vector2f{100, 50});
    }
}