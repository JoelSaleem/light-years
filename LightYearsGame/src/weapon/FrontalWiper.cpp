#include "weapon/FrontalWiper.h"
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/Core.h"
#include "weapon/Bullet.h"
#include "framework/World.h"

namespace ly
{
    FrontalWiper::FrontalWiper(
        Actor *owner,
        float cooldownTime,
        sf::Vector2f localPosOffset,
        float width)
        : Shooter{owner},
          mWidth{width},
          mShooter1{owner, cooldownTime, {localPosOffset.x, localPosOffset.y - width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
          mShooter2{owner, cooldownTime, {localPosOffset.x, localPosOffset.y - width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
          mShooter3{owner, cooldownTime, {localPosOffset.x, localPosOffset.y + width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
          mShooter4{owner, cooldownTime, {localPosOffset.x, localPosOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
          mShooter5{owner, 0.1, {localPosOffset.x, localPosOffset.y + width / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
          mShooter6{owner, 0.1, {localPosOffset.x, localPosOffset.y - width / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
    {
    }

    void FrontalWiper::IncrementLevel(int amt)
    {
        Shooter::IncrementLevel(amt);

        mShooter1.IncrementLevel(amt);
        mShooter2.IncrementLevel(amt);
        mShooter3.IncrementLevel(amt);
        mShooter4.IncrementLevel(amt);
    }

    void FrontalWiper::ShootImpl()
    {
        mShooter1.Shoot();
        mShooter2.Shoot();
        mShooter3.Shoot();
        mShooter4.Shoot();

        if (GetCurrentLevel() == GetMaxLevel())
        {
            mShooter5.Shoot();
            mShooter6.Shoot();
        }
    }
}