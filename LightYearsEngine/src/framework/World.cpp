#include <box2d/b2_body.h>
#include <framework/World.h>
#include <framework/Core.h>
#include <framework/Actor.h>
#include "framework/Application.h"
#include "gameplay/GameStage.h"

namespace ly
{
    World::World(Application *owningApp)
        : mOwningApp(owningApp), mBegunPlay{false},
          mPendingActors{}, mActors{}, mGameStages{},
          mCurrentStageIndex{-1}
    {
    }

    World::~World() {}

    void World::BeginPlayInternal()
    {
        if (!mBegunPlay)
        {
            mBegunPlay = true;
            BeginPlay();
            InitGameStages();
            NextGameStage();
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

        if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
        {
            mGameStages[mCurrentStageIndex]->TickStage(deltaTime);
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

    void World::InitGameStages() {}

    void World::AllGameStagesFinished() {}

    void World::NextGameStage()
    {
        ++mCurrentStageIndex;
        if (mCurrentStageIndex >= 0 && mCurrentStageIndex < mGameStages.size())
        {
            shared<GameStage> nextGameStage = mGameStages[mCurrentStageIndex];
            nextGameStage->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
            nextGameStage->StartStage();
        }
        else
        {
            AllGameStagesFinished();
        }
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

        for (auto iter = mGameStages.begin(); iter != mGameStages.end();)
        {
            if (iter->get()->IsStageFinished())
            {
                iter = mGameStages.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }

    void World::AddStage(const shared<GameStage> stage)
    {
        mGameStages.push_back(stage);
    }
}