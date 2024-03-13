#include <framework/World.h>
#include <framework/Core.h>
#include <framework/Actor.h>

namespace ly
{
    World::World(Application *owningApp) : mOwningApp(owningApp), mBegunPlay{false}, mPendingActors{}, mActors{}
    {
    }

    World::~World() {}

    void World::BeginPlayInternal()
    {
        if (!mBegunPlay)
        {
            mBegunPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        for (shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }

        for(shared<Actor> actor: mActors) {
            actor->Tick(deltaTime);
        }

        mPendingActors.clear();
        Tick(deltaTime);
    }

    void World::BeginPlay()
    {
        LOG("begin play");
    }

    void World::Tick(float deltaTime)
    {
        LOG("tick at frame rate: %f", 1.f / deltaTime);
    }
}