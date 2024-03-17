#pragma once
#include <framework/Application.h>
#include <framework/Core.h>
#include "player/PlayerSpaceship.h"

namespace ly
{
    class PlayerSpaceship;
    class GameApplication : public Application
    {
    public:
        GameApplication();
    private:
        weak<PlayerSpaceship> testPlayerSpaceship;
    };
}
