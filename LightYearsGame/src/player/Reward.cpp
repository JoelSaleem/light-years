#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "weapon/ThreeWayShooter.h"
#include "weapon/FrontalWiper.h"
#include "framework/World.h"

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
        PlayerSpaceship *playerSpaceship = dynamic_cast<PlayerSpaceship *>(other);
        if (playerSpaceship != nullptr && !playerSpaceship->IsPendingDestroy())
        {
            mRewardFunc(playerSpaceship);
            Destroy();
        }
    }

    weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/pill_green.png", RewardHealth);
	}

    weak<Reward> CreateThreewayShooterReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/bolt_gold.png", RewardThreewayShooter);
    }

    weak<Reward> CreateFrontalWiperReward(World *world)
    {
        return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/bold_silver.png", RewardFrontalWiper);
    }

    weak<Reward> CreateReward(World *world, const std::string &texturePath, RewardFunc rewardFunc)
    {
        weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc);
        return reward;
    }

    void RewardHealth(PlayerSpaceship *player)
    {
        static float rewardAmt = 10.f;
        if (player && !player->IsPendingDestroy())
        {
            player->GetHealthComponent().ChangeHealth(rewardAmt);
        }
    }

    void RewardThreewayShooter(PlayerSpaceship *player)
    {
        if (player && !player->IsPendingDestroy())
        {
            player->SetShooter(unique<Shooter>{new ThreeWayShooter{player, 0.4, {50, 0}}});
        }
    }

    void RewardFrontalWiper(PlayerSpaceship *player)
    {
        if (player && !player->IsPendingDestroy())
        {
            player->SetShooter(unique<Shooter>{new FrontalWiper{player, 0.4, {50, 0}}});
        }
    }
}
