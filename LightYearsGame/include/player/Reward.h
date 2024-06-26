#pragma once

#include <functional>
#include "framework/Actor.h"

namespace ly
{
    class PlayerSpaceship;
    using RewardFunc = std::function<void(PlayerSpaceship *)>;
    class Reward : public Actor
    {
    public:
        Reward(
            World *world,
            const std::string &texturePath,
            RewardFunc rewardFunc,
            float speed = 200.f);

        virtual void BeginPlay() override;

        virtual void Tick(float deltaTime) override;

    private:
        virtual void OnActorBeginOverlap(Actor *other) override;

        float mSpeed;
        RewardFunc mRewardFunc;
    };

    weak<Reward> CreateHealthReward(World *world);
    weak<Reward> CreateThreewayShooterReward(World *world);
    weak<Reward> CreateFrontalWiperReward(World *world);

    weak<Reward> CreateReward(World *world, const std::string &texturePath, RewardFunc rewardFunc);

    void RewardHealth(PlayerSpaceship *player);
    void RewardFrontalWiper(PlayerSpaceship *player);
    void RewardThreewayShooter(PlayerSpaceship *player);

    using RewardFactoryFunc = std::function<weak<Reward>(World *)>;
}