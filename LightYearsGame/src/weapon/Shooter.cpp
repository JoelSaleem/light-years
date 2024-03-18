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

    Shooter::Shooter(Actor *owner) : mOwner{owner} {}
}