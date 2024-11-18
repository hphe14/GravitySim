#include <cmath>

#include "Calculations.h"



float squared(const sf::Vector2f& vec){
    return (vec.x * vec.x + vec.y * vec.y);
}

float magnitude(const sf::Vector2f& vec) {
    return std::sqrt(squared(vec));
}


float DotProd(const sf::Vector2f& vec1, const sf::Vector2f& vec2){
    return (vec1.x * vec2.x + vec1.y * vec2.y );
}


sf::Vector2f Tangent(const sf::Vector2f& vec) {
    return sf::Vector2f(-vec.y, vec.x); // Rotate 90 degrees
}

sf::Vector2f normalize(const sf::Vector2f& vec) {
    float mag = magnitude(vec);
    return mag > 0 ? vec / mag : sf::Vector2f(0, 0);
}


void GravForce(Object& object, Object& objectB){
    
    float gravConstant = 100.f;
    const float minDistance = 1000.0f;
    float mass = object.getMass();
    float massB = objectB.getMass();

    sf::Vector2f distance = (objectB.getPosition() - object.getPosition());

    float distanceSqr = squared(distance);
    distanceSqr = std::max(distanceSqr, minDistance);
    sf::Vector2f gravForceDirection = normalize(distance);

    sf::Vector2f gravForce = gravForceDirection *gravConstant * mass*massB / distanceSqr  ;

    sf::Vector2f accel_A = (gravForce/mass);
    sf::Vector2f accel_B = (-gravForce/massB);  
    
    object.setAcceleration(accel_A);
    objectB.setAcceleration(accel_B);
    
}



