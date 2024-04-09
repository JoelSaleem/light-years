#pragma once
#include "weapon/Shooter.h"
#include "weapon/BulletShooter.h"
#include <SFML/System.hpp>

namespace ly
{
    class ThreeWayShooter : public Shooter
    {
    public:
        ThreeWayShooter(Actor *owner, float cooldownTime = 0.1f, sf::Vector2f localPosOffset = {0.f, 0.f});
        virtual bool IsOnCooldown() const override;

        BulletShooter mShooterLeft;
        BulletShooter mShooterRight;
        BulletShooter mShooterMid;

        BulletShooter mTopLevelShooterLeft;
        BulletShooter mTopLevelShooterRight;
        virtual void IncrementLevel(int amt) override;
        

    private:
        virtual void ShootImpl() override;
         
    };
}