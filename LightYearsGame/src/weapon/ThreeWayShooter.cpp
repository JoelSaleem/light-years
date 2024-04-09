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
        sf::Vector2f localPosOffset)
        : Shooter{owner},
          mShooterLeft{owner, cooldownTime, localPosOffset, -30.f},
          mShooterMid{owner, cooldownTime, localPosOffset},
          mShooterRight{owner, cooldownTime, localPosOffset, 30.f},
          mTopLevelShooterLeft{owner, cooldownTime, localPosOffset + sf::Vector2f{10, 10}, 15.f},
          mTopLevelShooterRight{owner, cooldownTime, localPosOffset + sf::Vector2f{10, -10}, -15.f}
    {
        mShooterLeft.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
        mShooterRight.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
        mShooterMid.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");

        mTopLevelShooterLeft.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
        mTopLevelShooterRight.SetBulletTexturePath("SpaceShooterRedux/PNG/Lasers/laserRed01.png");
    }

    bool ThreeWayShooter::IsOnCooldown() const
    {
        // if (mCooldownClock.getElapsedTime().asSeconds() > mCooldownTime)
        // {
        //     return false;
        // }

        // return true;
        return Shooter::IsOnCooldown();
    }

    void ThreeWayShooter::IncrementLevel(int amt)
    {
        Shooter::IncrementLevel(amt);
        mShooterLeft.IncrementLevel(amt);
        mShooterMid.IncrementLevel(amt);
        mShooterRight.IncrementLevel(amt);

        mTopLevelShooterLeft.IncrementLevel(amt);
        mTopLevelShooterRight.IncrementLevel(amt);
    }

    void ThreeWayShooter::ShootImpl()
    {
        mShooterLeft.Shoot();
        mShooterRight.Shoot();
        mShooterMid.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            mTopLevelShooterLeft.Shoot();
            mTopLevelShooterRight.Shoot();
        }
    }
}