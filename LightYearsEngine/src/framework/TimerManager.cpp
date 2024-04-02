#include "framework/TimerManager.h"

namespace ly
{
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
        for (Timer &timer : mTimers)
        {
            timer.TickTime(deltaTime);
        }
    }
}