#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "spaceship/Spaceship.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include "framework/AssetManager.h"

ly::Application *GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication() : Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDir(GetResourceDir());

        weak<World> newWorld = LoadWorld<World>();
        newWorld.lock()->SpawnActor<Actor>();

        testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock().get()->SetActorLocation(sf::Vector2f{300, 490});
        testPlayerSpaceship.lock().get()->SetActorRotation(-90.f);

        weak<Spaceship> testSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
        testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
        testPlayerSpaceship.lock().get()->SetActorLocation(sf::Vector2f{100, 50});
        counter = 0.f;
    }

    void GameApplication::Tick(float deltaTime)
    {
        counter += deltaTime;
        if (counter > 10.f)
        {
            if (!testPlayerSpaceship.expired())
            {
                testPlayerSpaceship.lock()->Destroy(); 
            }
        }
    }
}
