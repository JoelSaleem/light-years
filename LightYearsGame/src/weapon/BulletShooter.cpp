#include "weapon/BulletShooter.h"
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"

namespace ly
{
    BulletShooter::BulletShooter(
        Actor *owner,
        float cooldownTime,
        sf::Vector2f localPosOffset,
        float localRotationOffset,
        const std::string &bulletTexturePath)
        : Shooter{owner},
          mCooldownClock{},
          mCooldownTime{cooldownTime},
          mLocalPosOffset{localPosOffset},
          mLocalRotationOffset{localRotationOffset},
          mBulletTexturePath{bulletTexturePath}
    {
    }

    void BulletShooter::SetBulletTexturePath(const std::string &texturePath)
    {
        mBulletTexturePath = texturePath;
    }

    bool BulletShooter::IsOnCooldown() const
    {
        return !(mCooldownClock.getElapsedTime().asSeconds() > (mCooldownTime / GetCurrentLevel()));
    }

    void BulletShooter::IncrementLevel(int amt)
    {
        Shooter::IncrementLevel(amt);
    }

    void BulletShooter::ShootImpl()
    {
        sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
        sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

        mCooldownClock.restart();
        weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), mBulletTexturePath);
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPosOffset.x + ownerRightDir * mLocalPosOffset.y);
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
    }
}