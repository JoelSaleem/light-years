#pragma once
#include "framework/Core.h"
#include "framework/Object.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application;
    class Actor;
    class World: public Object
    {
    public:
        World(Application *owningApp);
        virtual ~World();

        void BeginPlayInternal();
        void TickInternal(float deltaTime);

        void Render(sf::RenderWindow &window);

        template <typename ActorType, typename... Args>
        weak<ActorType> SpawnActor(Args... args);

        sf::Vector2u GetWindowSize() const;
        void CleanCycle();


    private:
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        Application *mOwningApp;
        bool mBegunPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPendingActors;
    };

    template <typename ActorType, typename... Args>
    inline weak<ActorType> World::SpawnActor(Args... args)
    {
        shared<ActorType> newActor(new ActorType{this, args...});
        mPendingActors.push_back(newActor);

        return newActor;
    }
}