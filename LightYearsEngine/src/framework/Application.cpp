#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"

namespace ly
{

    Application::Application(
        uint windowWidth, uint windowHeight,
        const std::string &title, sf::Uint32 style) : mWindow{sf::VideoMode(windowWidth, windowHeight), title, style},
                                                      mTargetFrameRate{60.f},
                                                      mTickClock{},
                                                      currentWorld{nullptr},
                                                      mCleanCycleClock{},
                                                      mCleanCycleInterval{2.f}
    {
    }

    void Application::Run()
    {
        mTickClock.restart();
        float accumulatedTime = 0.f;
        float targetDeltaTime = 1.f / mTargetFrameRate;
        while (mWindow.isOpen())
        {
            sf::Event windowEvent;
            while (mWindow.pollEvent(windowEvent))
            {
                if (windowEvent.type == sf::Event::EventType::Closed)
                {
                    mWindow.close();
                }
            }

            float deltaTime = mTickClock.restart().asSeconds();
            accumulatedTime += deltaTime;
            while (accumulatedTime > targetDeltaTime)
            {
                accumulatedTime -= targetDeltaTime;
                TickInternal(targetDeltaTime);

                RenderInternal();
            }
        }
    }

    void Application::Tick(float deltaTime)
    {
        if (currentWorld)
        {
            currentWorld->BeginPlayInternal();
            currentWorld->TickInternal(deltaTime);
        }
    }

    void Application::Render()
    {
        if (currentWorld)
        {
            currentWorld->Render(mWindow);
        }
    }

    void Application::TickInternal(float deltaTime)
    {

        Tick(deltaTime);

        if (currentWorld)
        {
            currentWorld->TickInternal(deltaTime);
        }

        if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval) {
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
        }
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }
}