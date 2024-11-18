#include <random>
#include <cmath>
#include <iostream>

#include "Spawn.h"
#include "Calculations.h"






std::vector<Object> TwoBody(){
    std::vector<Object> planets;

    Object planetA(20.f, sf::Color::Red);
    planetA.setPosition(430, 630);
    planetA.initalVelocity(0,1);
    planetA.objectMass(20.f);
    planets.push_back(planetA);

    Object planetB(20.f, sf::Color::Blue);
    planetB.setPosition(830, 630);
    planetB.initalVelocity(0,-1);
    planetB.objectMass(20.f);
    planets.push_back(planetB);

    return planets;
}


std::vector<Object> ThreeBody(){
    std::vector<Object> planets;

    Object planetA(20.f, sf::Color::Red);
    planetA.setPosition(630, 380);
    planetA.initalVelocity(0.5,0);
    planetA.objectMass(15.f);
    planets.push_back(planetA);

    Object planetB(20.f, sf::Color::Blue);
    planetB.setPosition(830, 880);
    planetB.initalVelocity(-0.5,1);
    planetB.objectMass(15.f);
    planets.push_back(planetB);

    Object planetC(20.f, sf::Color::Green);
    planetC.setPosition(430, 880);
    planetC.initalVelocity(0.5,-1);
    planetC.objectMass(15.f);
    planets.push_back(planetC);

    return planets;
}

std::vector<Object> CentreMass(){
    std::vector<Object> planets;

    std::random_device rd;
    std::mt19937 gen(rd());


    std::uniform_real_distribution<float> angleDist(0, 2 * M_PI); 
    
    std::uniform_real_distribution<float> radiusDist(200, 250);

    for (int i=0; i  < 300; i++){
        float angle = angleDist(gen);
        float radius = radiusDist(gen);
      
        float x = 630 + radius * std::cos(angle);
        float y = 630 + radius * std::sin(angle);

        Object particles(1,sf::Color::Yellow);
        
        particles.objectMass(0.00001f);
        particles.setPosition(x, y);
        sf::Vector2f direction = normalize(particles.getPosition() - sf::Vector2f(630, 630));
        sf::Vector2f angularvel = Tangent(direction);

        particles.initalVelocity(angularvel.x*1.8, angularvel.y*1.8);

        planets.push_back(particles);

    }

    Object centremass(10,sf::Color::Red);
    centremass.setPosition(630, 630);
    centremass.initalVelocity(0,0);
    centremass.objectMass(10.f);
    planets.push_back(centremass);


    return planets;
}



