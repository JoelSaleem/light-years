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
}