#include "framework/TimerManager.h"

namespace ly
{
    unsigned int TimerHandle::timerKeyCounter = 0;

    TimerHandle::TimerHandle() : mTimerKey{GetNextTimerKey()} {}

    bool operator==(const TimerHandle &lhs, const TimerHandle rhs)
    {
        return lhs.GetTimerKey() == rhs.GetTimerKey();
    }

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

    unique<TimerManager> TimerManager::timerManager{nullptr};

    TimerManager::TimerManager() : mTimers{} {}

    TimerManager &TimerManager::Get()
    {
        if (!timerManager)
        {
            timerManager = std::move(unique<TimerManager>(new TimerManager{}));
        }

        return *timerManager;
    }

    void TimerManager::UpdateTimers(float deltaTime)
    {
        for (auto iter = mTimers.begin(); iter != mTimers.end();)
        {
            if (iter->second.Expired())
            {
                iter = mTimers.erase(iter);
            }
            else
            {
                iter->second.TickTime(deltaTime);
                iter++;
            }
        }
    }

    void TimerManager::ClearTimer(TimerHandle timerHandle)
    {
        auto iter = mTimers.find(timerHandle);
        if (iter != mTimers.end())
        {
            iter->second.SetExpired();
        }
    }
}