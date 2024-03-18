#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
    sf::Vector2f RotationToVector(float rot);

    float DegreesToRadians(float deg);

    float RadiansToDegrees(float rad);

    template <typename T>
    float GetVectorLength(const sf::Vector2<T> &vec)
    {
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    template <typename T>
    sf::Vector2<T> &ScaleVector(sf::Vector2<T> &vecToScale, float amt)
    {
        vecToScale.x *= amt;
        vecToScale.y *= amt;

        return vecToScale;
    }

    template <typename T>
    sf::Vector2<T> &Normalize(sf::Vector2<T> &vec)
    {
        float vecLen = GetVectorLength<T>(vec);
        if (vecLen == 0.f)
            return vec;

        return ScaleVector(vec, 1.f / vecLen);
    }
}