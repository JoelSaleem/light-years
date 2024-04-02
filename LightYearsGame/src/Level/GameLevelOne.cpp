#include "Level/GameLevelOne.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/TimerManager.h"
#include "spaceship/Spaceship.h"
#include "Enemy/Vanguard.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
        : mListener{weakRef, callback},
          mDuration{duration},
          mIsExpired{false},
          mRepeat{repeat},
          mTimeCounter{0}
    {
    }

    void Timer::TickTime(float deltaTime)
    {
        if (Expired())
        {
            return;
        }

        mTimeCounter += deltaTime;
        if (mTimeCounter >= mDuration)
        {
            mListener.second();

            if (mRepeat)
            {
                mTimeCounter = 0.f;
            }
            else
            {
                SetExpired();
            }
        }
    }

    void Timer::SetExpired()
    {
        mIsExpired = true;
    }

    bool Timer::Expired() const
    {
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
    }

    GameLevelOne::GameLevelOne(Application *owningApp)
        : World{owningApp}
    {
        testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
        testPlayerSpaceship.lock().get()->SetActorLocation(sf::Vector2f{300, 490});
        testPlayerSpaceship.lock().get()->SetActorRotation(-90.f);

        weak<Vanguard> testSpaceship = SpawnActor<Vanguard>();
        testSpaceship.lock().get()->SetActorLocation(sf::Vector2f{100, 50});
    }

    void GameLevelOne::BeginPlay()
    {
        TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 3, true);
    }

    void GameLevelOne::TimerCallback_Test()
    {
        LOG("callback called");
    }
}