#include "player/Reward.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Reward::Reward(
        World *world,
        const std::string &texturePath,
        RewardFunc rewardFunc,
        float speed)
        : Actor{world, texturePath},
          mSpeed{speed},
          mRewardFunc{rewardFunc}
    {
    }

    void Reward::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Reward::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        AddActorLocationOffset({0.f, mSpeed * deltaTime});
    }

    void Reward::OnActorBeginOverlap(Actor *other)
    {
        // Todo: clean up casting
        PlayerSpaceship *playerSpaceship = static_cast<PlayerSpaceship *>(other);

        if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
        {
            mRewardFunc(playerSpaceship);
        }
    }
}
