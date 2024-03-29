#include "VFX/Explosion.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "VFX/Particle.h"

namespace ly
{
    Explosion::Explosion(
        int particleAmt,
        float lifeTimeMin,
        float lifetimeMax,
        float sizeMin,
        float sizeMax,
        float speedMin,
        float speedMax,
        const sf::Color &particleColor)
        : mParticleAmt{particleAmt},
          mLifetimeMin{lifeTimeMin},
          mLifetimeMax{lifetimeMax},
          mSizeMin{sizeMin},
          mSizeMax{sizeMax},
          mSpeedMin{speedMin},
          mSpeedMax{speedMax},
          mSpawnColor{particleColor},
          mParticleImagePaths{
              "SpaceShooterRedux/PNG/Effects/star1.png",
              "SpaceShooterRedux/PNG/Effects/star2.png",
              "SpaceShooterRedux/PNG/Effects/star3.png"}
    {
    }

    void Explosion::SpawnExplosion(World *world, const sf::Vector2f &location)
    {
        if (!world)
        {
            return;
        }

        for (int i = 0; i < mParticleAmt; i++)
        {
            std::string particleImagePath = mParticleImagePaths[(int)RandomRange(0, mParticleImagePaths.size())];
            weak<Particle> newParticle = world->SpawnActor<Particle>(particleImagePath);

            newParticle.lock()->RandomLifetime(mLifetimeMin, mLifetimeMax);
            newParticle.lock()->SetActorLocation(location);
            newParticle.lock()->RandomSize(mSizeMin, mSizeMax);
            newParticle.lock()->RandomVelocity(mSpeedMin, mSpeedMax);
            newParticle.lock()->GetSprite().setColor(mSpawnColor);
        }
    }

}