#include "Enemy/UFO.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    UFO::UFO(World *owningWorld, const std::string &texturePath,
             const sf::Vector2f &velocity,
             float rotationSpeed)
        : EnemySpaceship{owningWorld, texturePath},
          mShooter1{new BulletShooter{this, 1.f, {0, 0}, -60}},
          mShooter2{new BulletShooter{this, 1.f, {0, 0}, 60}},
          mShooter3{new BulletShooter{this, 1.f, {0, 0}, 180}},
          mRotationSpeed{rotationSpeed}
    {
        SetVelocity(velocity);
        SetActorRotation(90.f);
    }

    void UFO::Tick(float deltaTime)
    {
        EnemySpaceship::Tick(deltaTime);
        Shoot();
        AddActorRotationOffset(mRotationSpeed * deltaTime);
    }

    void UFO::Shoot()
    {
        mShooter1->Shoot();
        mShooter2->Shoot();
        mShooter3->Shoot();
    }
}