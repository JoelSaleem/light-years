#include <SFML/Graphics.hpp>
#include "config.h"
#include "gameFramework/GameApplication.h"
#include "framework/AssetManager.h" 
#include "Level/GameLevelOne.h"

ly::Application *GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication() : Application{600, 980, "Light Years", sf::Style::Titlebar | sf::Style::Close}
    {
        AssetManager::Get().SetAssetRootDir(GetResourceDir());

        weak<GameLevelOne> newWorld = LoadWorld<GameLevelOne>();
    }
}
