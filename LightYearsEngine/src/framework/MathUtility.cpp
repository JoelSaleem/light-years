#include <random>
#include "framework/MathUtility.h"

namespace ly
{
    const float PI = 3.1415926535;

    sf::Vector2f RotationToVector(float rot)
    {
        float rad = DegreesToRadians(rot);
        return sf::Vector2f{std::cos(rad), std::sin(rad)};
    }

    float DegreesToRadians(float deg)
    {
        return deg * PI / 180.f;
    }

    float RadiansToDegrees(float rad)
    {
        return rad * 180.f / PI;
    }

    float LerpFloat(float a, float b, float alpha)
    {
        if (alpha > 1)
        {
            alpha = 1;
        }
        if (alpha < 0)
        {
            alpha = 0;
        }

        return a + (b - a) * alpha;
    }

    sf::Color LerpColor(const sf::Color &a, const sf::Color &b, float alpha)
    {
        float r = LerpFloat(a.r, b.r, alpha);
        float g = LerpFloat(a.g, b.g, alpha);
        float blu = LerpFloat(a.b, b.b, alpha);
        float alp = LerpFloat(a.a, b.a, alpha);

        return sf::Color(r, g, blu, alp);
    }

    sf::Vector2f LerpVector(const sf::Vector2f &a, const sf::Vector2f &b, float alpha)
    {
        float x = LerpFloat(a.x, b.x, alpha);
        float y = LerpFloat(a.y, b.y, alpha);
        return sf::Vector2f{x, y};
    }

    float RandomRange(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> distribution(min, max);

        return distribution(gen);
    }

    sf::Vector2f RandomUnitVector()
    {
        float randomX = RandomRange(-1, 1);
        float randomY = RandomRange(-1, 1);

        sf::Vector2f randomVec{randomX, randomY};
        Normalize(randomVec);

        return randomVec;
    }
}