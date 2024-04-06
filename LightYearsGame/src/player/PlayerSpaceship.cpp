#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"
#include "player/PlayerSpaceship.h"
#include "framework/MathUtility.h"
#include <SFML/System.hpp>

const uint PLAYER_TEAM_ID = 1;

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World *owningWorld, const std::string &texturePath)
        : Spaceship{owningWorld, texturePath},
          mMoveInput{0.f, 0.f},
          mSpeed{100.f},
          mShooter{new ThreeWayShooter{this, 0.01f, {50.f, 0.f}}}
    {
        SetTeamID(PLAYER_TEAM_ID);
    }

    void PlayerSpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
    };

    void PlayerSpaceship::HandleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            mMoveInput.y = -1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {

            mMoveInput.y = 1.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

            mMoveInput.x = 1.f;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

            mMoveInput.x = -1.f;
        }

        ClampInputOnEdge();
        NormalizeInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0.f;
    }

    void PlayerSpaceship::NormalizeInput()
    {
        Normalize(mMoveInput);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        sf::Vector2u maxBounds = Actor::GetWindowSize();
        sf::Vector2f actorLocation = Actor::GetActorLocation();
        if (actorLocation.x < 0 && mMoveInput.x == -1.f)
        {
            mMoveInput.x = 0;
        }
        if (actorLocation.x > maxBounds.x && mMoveInput.x == 1.f)
        {
            mMoveInput.x = 0;
        }

        if (actorLocation.y < 0 && mMoveInput.y == -1.f)
        {
            mMoveInput.y = 0;
        }
        if (actorLocation.y > maxBounds.y && mMoveInput.y == 1.f)
        {
            mMoveInput.y = 0;
        }
    }

    void PlayerSpaceship::Shoot()
    {
        if (!mShooter)
        {
            return;
        }

        mShooter->Shoot();
    }
}