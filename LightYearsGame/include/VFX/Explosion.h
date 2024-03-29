#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "framework/Core.h"

namespace ly
{
    class World;
    class Explosion
    {
    public:
        Explosion(
            int particleAmt = 20,
            float lifeTimeMin = 0.5,
            float lifetimeMax = 1.f,
            float sizeMin = 1, float sizeMax = 2, float speedMin = 200, float speedMax = 400, const sf::Color &particleColor = sf::Color{255, 128, 0, 255});
        void SpawnExplosion(World *world, const sf::Vector2f &location);

    private:
        int mParticleAmt;

        float mLifetimeMin;
        float mLifetimeMax;

        float mSizeMin;
        float mSizeMax;

        float mSpeedMax;
        float mSpeedMin;

        sf::Color mSpawnColor;

        List<std::string> mParticleImagePaths;
    };
}