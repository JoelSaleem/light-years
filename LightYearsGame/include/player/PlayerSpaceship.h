#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World *owningWorld, const std::string &texturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        virtual void Tick(float deltaTime) override;
        void SetSpeed(float speed) { mSpeed = speed; };
        float GetSpeech() { return mSpeed; }

    private:
        void HandleInput();
        void NormalizeInput();
        void ConsumeInput(float deltaTime);
        sf::Vector2f mMoveInput;
        float mSpeed;
    };
}