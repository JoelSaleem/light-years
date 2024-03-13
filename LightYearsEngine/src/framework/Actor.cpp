#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World *owningWorld) : mOwningWorld{owningWorld}, mBegunPlay{false} {}
    Actor::~Actor() {}

    void Actor::BeginPlayInternal()
    {
        if (!mBegunPlay)
        {
            mBegunPlay = true;
            BeginPlay();
        }
    }

    void Actor::BeginPlay()
    {
        LOG("actor begun");
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("actor tick");
    }
}