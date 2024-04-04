#pragma once
#include "weapon/Shooter.h"
#include <SFML/System.hpp>

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor *owner, float cooldownTime = 0.2f, sf::Vector2f localPosOffset = {0.f, 0.f}, float localRotationOffset = 0.f);
        virtual bool IsOnCooldown() const override;

    private:
        virtual void ShootImpl() override;
        sf::Clock mCooldownClock;
        float mCooldownTime;

        sf::Vector2f mLocalPosOffset;
        float mLocalRotationOffset;
    };
}