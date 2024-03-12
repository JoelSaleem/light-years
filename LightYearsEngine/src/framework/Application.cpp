#include "framework/Application.h"
#include <framework/Core.h>

namespace ly
{

    Application::Application() : mWindow{sf::VideoMode(1024, 1440), "Light Years"},
                                 mTargetFrameRate{60},
                                 mTickClock{}
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
        LOG("ticking at framerate: %f\n", 1.f / deltaTime);
    }

    void Application::Render()
    {
        sf::RectangleShape rect{sf::Vector2f{100, 100}};
        rect.setOrigin(50, 50);
        rect.setFillColor(sf::Color::Green);
        rect.setPosition(mWindow.getSize().x / 2.f, mWindow.getSize().y / 2.f);

        mWindow.draw(rect);
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
    }

    void Application::RenderInternal()
    {
        mWindow.clear();

        Render();

        mWindow.display();
    }
}