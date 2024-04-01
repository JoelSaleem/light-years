#pragma once
#include "Enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class Vanguard : public EnemySpaceship
    {
    public:
        Vanguard(World *owningWorld, const std::string &texturePath = "SpaceShooterRedux/PNG/Enemies/enemyRed1.png", const sf::Vector2f &velocity = {0, 50});
        virtual void Tick(float deltaTime) override;

    private:
        unique<BulletShooter> mShooter;
        virtual void Shoot() override;
    };

}