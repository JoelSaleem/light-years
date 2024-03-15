#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
    class World;
    class Actor : public Object
    {
    public:
        Actor(World *owningWorld, const std::string &texturePath = "");
        virtual ~Actor();
        
        void BeginPlayInternal();
        virtual void BeginPlay();
        
        void TickInternal(float deltaTime);
        virtual void Tick(float deltaTime);
        
        void SetTexture(const std::string &texturePath);
        void Render(sf::RenderWindow &window);

    private:
        World *mOwningWorld;
        bool mBegunPlay;

        sf::Sprite mSprite;
        sf::Texture mTexture;
    };
}