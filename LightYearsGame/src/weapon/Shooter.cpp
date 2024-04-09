#include "weapon/Shooter.h"

namespace ly
{

    void Shooter::Shoot()
    {
        if (!CanShoot() || IsOnCooldown())
        {
            return;
        }

        ShootImpl();
    }

    void Shooter::IncrementLevel(int amt)
    {
        if (mCurrentLevel == mMaxLevel)
        {
            return;
        }

        mCurrentLevel += amt;
    }

    Shooter::Shooter(Actor *owner)
        : mOwner{owner},
          mMaxLevel{4},
          mCurrentLevel{1}
    {
    }

}
