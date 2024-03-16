#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
    sf::Vector2f RotationToVector(float rot);

    float DegreesToRadians(float deg);

    float RadiansToDegrees(float rad);
}