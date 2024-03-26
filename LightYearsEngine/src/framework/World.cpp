#include <box2d/b2_body.h>
#include <framework/World.h>
#include <framework/Core.h>
#include <framework/Actor.h>
#include "framework/Application.h"

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

    void World::Render(sf::RenderWindow &window)
    {
        for (auto &actor : mActors)
        {
            actor->Render(window);
        }
    }

    void World::TickInternal(float deltaTime)
    {
        for (shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayInternal();
        }
        mPendingActors.clear();

        for (auto iter = mActors.begin(); iter != mActors.end();)
        {

            iter->get()->TickInternal(deltaTime);
            iter++;
        }

        Tick(deltaTime);
    }

    void World::BeginPlay()
    {
    }

    void World::Tick(float deltaTime)
    {
        // LOG("tick at frame rate: %f", 1.f / deltaTime);
    }

    sf::Vector2u World::GetWindowSize() const
    {
        return mOwningApp->GetWindowSize();
    }

    void World::CleanCycle()
    {
        for (auto iter = mActors.begin(); iter != mActors.end();)
        {
            if (iter->get()->IsPendingDestroy())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
}