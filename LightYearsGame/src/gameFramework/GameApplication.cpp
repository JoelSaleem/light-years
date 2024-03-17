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
        testPlayerSpaceship.lock().get()->SetActorRotation(-48.f);
    }
}
