#include "player/PlayerSpaceship.h"
#include <SFML/System.hpp>

namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World *owningWorld, const std::string &texturePath)
        : Spaceship{owningWorld, texturePath},
          mMoveInput{0.f, 0.f},
          mSpeed{100.f}
    {
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
    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.x = mMoveInput.y = 0.f;
    }
}