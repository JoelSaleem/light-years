#pragma once
#include "spaceship/Spaceship.h"
#include "weapon/BulletShooter.h"
#include "weapon/Shooter.h"

namespace ly
{
    class BulletShooter;
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World *owningWorld, const std::string &texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        virtual void Tick(float deltaTime) override;
        void SetSpeed(float speed) { mSpeed = speed; };
        float GetSpeed() { return mSpeed; }
        virtual void Shoot() override;
        void SetShooter(unique<Shooter> &&newShooter);

    private:
        void HandleInput();
        void NormalizeInput();
        void ClampInputOnEdge();
        void ConsumeInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;

        unique<Shooter> mShooter;
    };
}