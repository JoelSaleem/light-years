#include "player/PlayerManager.h"

namespace ly
{
    unique<PlayerManager> PlayerManager::mPlayerManager{nullptr};

    PlayerManager::PlayerManager() : mPlayers{}
    {
    }

    Player &PlayerManager::CreateNewPlayer()
    {
        mPlayers.emplace(mPlayers.begin(), Player{});
        return mPlayers.front();
    }

    Player *PlayerManager::GetPlayer(int playerIndex)
    {
        if (playerIndex < 0 || playerIndex > mPlayers.size() - 1)
        {
            return nullptr;
        }

        return &mPlayers[playerIndex];
    }

    const Player *PlayerManager::GetPlayer(int playerIndex) const
    {
        if (playerIndex < 0 || playerIndex > mPlayers.size() - 1)
        {
            return nullptr;
        }

        return &mPlayers[playerIndex];
    }

    PlayerManager &PlayerManager::Get()
    {
        if (!mPlayerManager)
        {
            mPlayerManager = std::move(unique<PlayerManager>({new PlayerManager{}}));
        }

        return *mPlayerManager;
    }
}
