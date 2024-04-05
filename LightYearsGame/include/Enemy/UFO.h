#pragma once
#include "Enemy/EnemySpaceship.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    class UFO : public EnemySpaceship
    {
    public:
        UFO(World *owningWorld, const std::string &texturePath = "SpaceShooterRedux/PNG/ufoRed.png",
            const sf::Vector2f &velocity = {0, 150.f},
            float rotationSpeed = 40);
        virtual void Tick(float deltaTime) override;

    private:
        virtual void Shoot() override;
        unique<BulletShooter> mShooter1;
        unique<BulletShooter> mShooter2;
        unique<BulletShooter> mShooter3;
        float mRotationSpeed;
    };

}