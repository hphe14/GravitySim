#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"


float magnitude(const sf::Vector2f& vec);
float squared(const sf::Vector2f& vec);
float DotProd(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

sf::Vector2f Tangent(const sf::Vector2f& vec);
sf::Vector2f normalize(const sf::Vector2f& vec);

void GravForce(Object& object, Object& objectB);
