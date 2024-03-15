#include "framework/Actor.h"
#include "framework/Core.h"

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
        LOG("actor begun");
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("actor tick");
    }

    void Actor::SetTexture(const std::string &texturePath)
    {
        mTexture.loadFromFile(texturePath);
        mSprite.setTexture(mTexture);

        int textureWidth = mTexture.getSize().x;
        int textureHeight = mTexture.getSize().y;
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