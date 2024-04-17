#include <box2d/b2_body.h>
#include <framework/World.h>
#include <framework/Core.h>
#include <framework/Actor.h>
#include "framework/Application.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace ly
{
    World::World(Application *owningApp)
        : mOwningApp(owningApp), mBegunPlay{false},
          mPendingActors{}, mActors{}, mGameStages{}
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
            StartStages();
        }
    }

    void World::Render(sf::RenderWindow &window)
    {
        for (auto &actor : mActors)
        {
            actor->Render(window);
        }

        RenderHUD(window);
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

        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->TickStage(deltaTime);
        }

        Tick(deltaTime);
        if (mHUD && !mHUD->HasInit())
        {
            mHUD->NativeInit(mOwningApp->GetWindow());
        }
    }

    void World::BeginPlay()
    {
    }

    void World::Tick(float deltaTime)
    {
        // LOG("tick at frame rate: %f", 1.f / deltaTime);
    }

    void World::InitGameStages() {}

    void World::AllGameStagesFinished()
    {
        LOG("all stages finished");
    }

    void World::NextGameStage()
    {
        mCurrentStage = mGameStages.erase(mCurrentStage);
        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
        }
        else
        {
            AllGameStagesFinished();
        }
    }

    void World::StartStages()
    {
        mCurrentStage = mGameStages.begin();
        if (mCurrentStage != mGameStages.end())
        {
            mCurrentStage->get()->StartStage();
            mCurrentStage->get()->onStageFinished.BindAction(
                GetWeakRef(),
                &World::NextGameStage);
        }
    }

    void World::RenderHUD(sf::RenderWindow &window)
    {
        if (mHUD)
        {
            mHUD->Draw(mOwningApp->GetWindow());
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
    }

    void World::AddStage(const shared<GameStage> stage)
    {
        mGameStages.push_back(stage);
    }

    bool World::DispatchEvent(const sf::Event &event)
    {
        if (mHUD)
        {
            return mHUD->HandleEvent(event);
        }

        return false;
    }
}