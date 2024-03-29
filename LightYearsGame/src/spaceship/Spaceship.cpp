#include <functional>
#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "VFX/Explosion.h"

namespace ly
{
    Spaceship::Spaceship(
        World *owningWorld, const std::string &texturePath) : Actor{owningWorld, texturePath},
                                                              mVelocity{sf::Vector2f{0.f, 0.f}},
                                                              mHealthComp{100.f, 100.f},
                                                              mBlinkTime{0.f},
                                                              mBlinkDuration{0.2f},
                                                              mBlinkColorOffset{255, 0, 0, 255}

    {
    }

    void Spaceship::Blink()
    {
        if (mBlinkTime == 0)
        {
            mBlinkTime = mBlinkDuration;
        }
    }

    void Spaceship::UpdateBlink(float deltaTime)
    {
        if (mBlinkTime > 0)
        {
            mBlinkTime -= deltaTime;

            mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

            GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
        }
    }

    void
    Spaceship::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset(GetVelocity() * deltaTime);
        UpdateBlink(deltaTime);
    }

    void Spaceship::SetVelocity(const sf::Vector2f &newVelocity)
    {
        mVelocity = newVelocity;
    }

    sf::Vector2f Spaceship::GetVelocity() const
    {
        return mVelocity;
    }

    void Spaceship::Shoot()
    {
    }

    void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
    {
        LOG("Health changed by: %f and is now: %f", amt, health, maxHealth);
    }

    void Spaceship::OnTakenDamage(float amt, float health, float maxHealth)
    {
        Blink();
    }

    void Spaceship::Blow()
    {
        Explosion *exp = new Explosion();
        exp->SpawnExplosion(GetWorld(), GetActorLocation());
        Destroy();
        delete exp;
    };

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);

        mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
        mHealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
    }

    void Spaceship::ApplyDamage(float amt)
    {
        mHealthComp.ChangeHealth(-amt);
    }
}