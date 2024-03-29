#include "weapon/Bullet.h"

namespace ly
{
    Bullet::Bullet(
        World *world, Actor *owner,
        const std::string &texturePath,
        float speed, float damage) : Actor{world, texturePath},
                                     mOwner{owner},
                                     mSpeed{speed}, mDamage{damage}
    {
        SetTeamID(owner->GetTeamID());
    };

    void Bullet::SetSpeed(float newSpeed) {}
    void Bullet::SetDamage(float newDamage) {}

    void Bullet::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        Move(deltaTime);

        if (IsActorOutOfWindowBounds())
        {
            Destroy();
        }
    }

    void Bullet::Move(float deltaTime)
    {
        AddActorLocationOffset(GetActorForwardDirection() * mSpeed * deltaTime);
    }

    void Bullet::BeginPlay()
    { 
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Bullet::OnActorBeginOverlap(Actor *other)
    {
        if (IsOtherHostile(other))
        {
             other->ApplyDamage(GetDamage()); 
             Destroy(); 
        }
    };
}