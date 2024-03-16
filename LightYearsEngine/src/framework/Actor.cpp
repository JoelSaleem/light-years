#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include <iostream>

namespace ly
{
    Actor::Actor(World *owningWorld, const std::string &texturePath) : mOwningWorld{owningWorld},
                                                                       mBegunPlay{false},
                                                                       mSprite{},
                                                                       mTexture{}
    {
        SetTexture(texturePath);
    }

    Actor::~Actor()
    {
        LOG("actor destroyed");
    }

    void Actor::BeginPlayInternal()
    {
        if (!mBegunPlay)
        {
            mBegunPlay = true;
            BeginPlay();
        }
    }

    void Actor::BeginPlay()
    {
    }

    void Actor::Tick(float deltaTime)
    {
    }

    void Actor::SetTexture(const std::string &texturePath)
    {
        AssetManager &assetManager = AssetManager::Get();

        mTexture = assetManager.LoadTexture(texturePath);
        if (!mTexture)
            return;

        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect{sf::Vector2i{}, sf::Vector2i{
                                                               textureWidth,
                                                               textureHeight,
                                                           }});
    }

    void Actor::Render(sf::RenderWindow &window)
    {
        if (IsPendingDestroy())
        {
            return;
        }

        window.draw(mSprite);
    }

    void Actor::TickInternal(float deltaTime)
    {
        if (IsPendingDestroy())
        {
            return;
        }

        Tick(deltaTime);
    }
}