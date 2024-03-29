#pragma once
#include "framework/Actor.h"
#include <SFML/Graphics.hpp>
#include "gameplay/HealthComponent.h"

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

        virtual void ApplyDamage(float amt) override; 

    private:
        virtual void OnHealthChanged(float amt, float health, float maxHealth);
        virtual void OnTakenDamage(float amt, float health, float maxHealth);
        virtual void Blow();

        sf::Vector2f mVelocity;
        HealthComponent mHealthComp;
    };

}