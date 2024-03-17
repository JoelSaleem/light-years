#include "spaceship/Spaceship.h"

namespace ly
{
    Spaceship::Spaceship(
        World *owningWorld, const std::string &texturePath) : Actor{owningWorld, texturePath},
                                                                   mVelocity{sf::Vector2f{0.f, 0.f}}
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
}