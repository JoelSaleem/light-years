#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "config.h"
#include <iostream>


ly::Application *GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication() : Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        weak<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();
        actorToDestroy = newWorld.lock()->SpawnActor<Actor>();

        actorToDestroy.lock().get()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
    }
}
