#include "weapon/ThreeWayShooter.h"
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"

namespace ly
{
    ThreeWayShooter::ThreeWayShooter(
        Actor *owner,
        float cooldownTime,
        sf::Vector2f localPosOffset
        )
        : Shooter{owner},
          mShooterLeft{owner, cooldownTime, localPosOffset, -30.f},
          mShooterMid{owner, cooldownTime, localPosOffset},
          mShooterRight{owner, cooldownTime, localPosOffset, 30.f}
    {
        mShooterLeft.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
        mShooterRight.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
        mShooterMid.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
    }

    bool ThreeWayShooter::IsOnCooldown() const
    { 
        // if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
        // {
        //     return false;
        // }

        // return true;
    }

    void ThreeWayShooter::ShootImpl()
    {
        mShooterLeft.Shoot();
        mShooterRight.Shoot();
        mShooterMid.Shoot();
        // sf::Vector2f ownerForwardDir = GetOwner()->GetActorForwardDirection();
        // sf::Vector2f ownerRightDir = GetOwner()->GetActorRightDirection();

        // mCooldownClock.restart();
        // weak<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        // newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + ownerForwardDir * mLocalPosOffset.x + ownerRightDir * mLocalPosOffset.y);
        // newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + mLocalRotationOffset);
    }
}