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
          mShooter4{owner, cooldownTime, {localPosOffset.x, localPosOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
    {
    }

    void FrontalWiper::ShootImpl()
    {
        mShooter1.Shoot();
        mShooter2.Shoot();
        mShooter3.Shoot();
        mShooter4.Shoot();
    }
}