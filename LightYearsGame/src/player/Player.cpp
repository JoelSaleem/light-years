#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Player::Player()
        : mPlayerLifeCount{3},
          mScore{0},
          mCurrentPlayerSpaceship{}
    {
    }

    weak<PlayerSpaceship> Player::SpawnSpaceship(World *world)
    {
        if (mPlayerLifeCount > 0)
        {
            mPlayerLifeCount--;
            auto windowSize = world->GetWindowSize();
            mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
            mCurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f{windowSize.x / 2.f, windowSize.y - 100.f});
            mCurrentPlayerSpaceship.lock()->SetActorRotation(-90.f);
            onLifeChange.Broadcast(mPlayerLifeCount);

            return mCurrentPlayerSpaceship;
        }
        else
        {
            onLifeExhausted.Broadcast();
        }

        return weak<PlayerSpaceship>{};
    }

    void Player::AddLifeCount(unsigned int count)
    {
        if (count > 0)
        {
            mPlayerLifeCount += count;
            onLifeChange.Broadcast(mPlayerLifeCount);
        }
    }

    void Player::AddScore(unsigned int amt)
    {
        if (amt == 0)
        {
            return;
        }

        mScore = amt;
        onScoreChange.Broadcast(amt);
    }
}
