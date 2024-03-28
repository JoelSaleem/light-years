#include "spaceship/Spaceship.h"
#include <functional>

namespace ly
{
    Spaceship::Spaceship(
        World *owningWorld, const std::string &texturePath) : Actor{owningWorld, texturePath},
                                                              mVelocity{sf::Vector2f{0.f, 0.f}},
                                                              mHealthComp{100.f, 100.f}
    {
    }

    void Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);

        AddActorLocationOffset(GetVelocity() * deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f &newVelocity)
    {
        mVelocity = newVelocity;
    }

    sf::Vector2f Spaceship::GetVelocity() const
    {
        return mVelocity;
    }

    void Spaceship::Shoot()
    {
    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
          

        std::function<void(float)> func = [](float var)
        {
            LOG("the value of var is: %f", var);
        };
        func(12);
    }
}