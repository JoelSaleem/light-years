#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "spaceship/Spaceship.h"
#include "config.h"
#include <SFML/Graphics.hpp>

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

        testPlayerSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
        testPlayerSpaceship.lock().get()->SetActorLocation(sf::Vector2f{300, 490});
        testPlayerSpaceship.lock().get()->SetActorRotation(-48.f);
        testPlayerSpaceship.lock().get()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPlayerSpaceship.lock().get()->SetVelocity(sf::Vector2f{10.f, 10.f});
    }
}
