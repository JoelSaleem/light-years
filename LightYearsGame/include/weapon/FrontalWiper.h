#pragma once
#include "weapon/Shooter.h"
#include "weapon/BulletShooter.h"
#include <SFML/System.hpp>

namespace ly
{
    class FrontalWiper : public Shooter
    {
    public:
        FrontalWiper(
            Actor *owner,
            float cooldownTime = 0.3f,
            sf::Vector2f localPosOffset = {0.f, 0.f},
            float width = 60.f);

        virtual void IncrementLevel(int amt = 1);

    private:
        virtual void ShootImpl() override;

        BulletShooter mShooter1;
        BulletShooter mShooter2;
        BulletShooter mShooter3;
        BulletShooter mShooter4;
        
        BulletShooter mShooter5;
        BulletShooter mShooter6;

        float mWidth;
    };
}