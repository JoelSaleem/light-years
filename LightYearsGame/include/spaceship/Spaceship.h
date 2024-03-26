#pragma once
#include "framework/Actor.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class Spaceship : public Actor
    {
    public:
        Spaceship(World *owningWorld, const std::string &texturePath = "");
        virtual void Tick(float deltaTime) override;
        void SetVelocity(const sf::Vector2f &newVelocity);
        sf::Vector2f GetVelocity() const;
        virtual void Shoot();
        virtual void BeginPlay() override;

    private:
        sf::Vector2f mVelocity;
    };

}