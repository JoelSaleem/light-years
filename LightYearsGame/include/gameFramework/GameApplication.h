#pragma once
#include <framework/Application.h>
#include <framework/Core.h>
#include "spaceship/Spaceship.h"

namespace ly
{
    class Spaceship;
    class GameApplication : public Application
    {
    public:
        GameApplication();
    private:
        weak<Spaceship> testPlayerSpaceship;
    };
}
