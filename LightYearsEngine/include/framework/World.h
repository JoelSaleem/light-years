#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application;
    class Actor;
    class World
    {
    public:
        World(Application *owningApp);
        virtual ~World();

        void BeginPlayInternal();
        void TickInternal(float deltaTime);

        void Render(sf::RenderWindow &window);

        template <typename ActorType>
        weak<ActorType> SpawnActor();

        sf::Vector2u GetWindowSize() const;

    private:
        void BeginPlay();
        void Tick(float deltaTime);
        Application *mOwningApp;
        bool mBegunPlay;

        List<shared<Actor>> mActors;
        List<shared<Actor>> mPendingActors;
    };

    template <typename ActorType>
    inline weak<ActorType> World::SpawnActor()
    {
        shared<ActorType> newActor{new ActorType{this}};
        mPendingActors.push_back(newActor);

        return newActor;
    }
}