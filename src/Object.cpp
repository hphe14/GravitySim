#include <iostream>
#include <cmath>

#include "Object.h"
#include "Calculations.h"


Object::Object(float radius,const sf::Color& color) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
   
}

void Object::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
    shape.setPosition(position);    
}

void Object::setAcceleration(sf::Vector2f a){  
    acceleration = a;
    velocity += acceleration;
}


float Object::objectMass(float m) {
    return mass = m;
}

float Object::getMass() {
    return mass;
}

float Object::getRadius() const { 
    return shape.getRadius();
}

sf::Vector2f Object::getPosition(){
     return shape.getPosition();
}

void Object::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void Object::initalVelocity(float vx, float vy){
    velocity.x = vx;
    velocity.y = vy;
       
}

void Object::move() {
    position += velocity; //* dt;
    shape.rotate(10.f);
    shape.setPosition(position);  

}


void Object::boundaryCollision(sf::RenderWindow& window){
    float radius = getRadius();
    auto windowSize = window.getSize();
    if (position.y + radius >= windowSize.y ){
        position.y = windowSize.y - radius;
        velocity.y = -velocity.y;       
    } else if (position.y - radius <= 0){
        position.y = radius;
        velocity.y = -velocity.y;      
    } 
    
    if (position.x +radius >= windowSize.x){
        position.x = windowSize.x -radius;
        velocity.x = -velocity.x;
    } else if (position.x - radius <= 0){
        position.x = radius;
        velocity.x = -velocity.x;
    }
}


void Object::ElasticCollision(Object& objectB){
    //initial velocity before collision
    sf::Vector2f vel1 = velocity;
    sf::Vector2f vel2 = objectB.velocity;

    float mass1 = mass;
    float mass2 = objectB.mass;
    
    sf::Vector2f normalVector = objectB.position - position;
    sf::Vector2f relVelocity = vel2 - vel1 ;
    
    float normalMagnitude = magnitude(normalVector);
       
    float minDistance = (objectB.getRadius() + getRadius());
    float distanceColl = normalMagnitude - minDistance;

    sf::Vector2f unitVector = normalize(normalVector);
    sf::Vector2f unitTangent = Tangent(unitVector);

    float scalarNormal_1 = DotProd(unitVector, vel1);
    float scalarTangential_1= DotProd(unitTangent, vel1);
    float scalarNormal_2 = DotProd(unitVector, vel2);
    float scalarTangential_2= DotProd(unitTangent, vel2);

    //new normal Velocities after collision
    float newNormalVel_1 = ( scalarNormal_1*(mass1 - mass2) + 2*mass2*scalarNormal_2 ) / (mass1+mass2);
    float newNormalVel_2 = ( scalarNormal_2*(mass2 - mass1) + 2*mass1*scalarNormal_1 ) / (mass1+mass2);

    //convert new normal and tangents to vectors
    sf::Vector2f newNormalVelVector_1 = newNormalVel_1 * unitVector;
    sf::Vector2f newNormalVelVector_2 = newNormalVel_2 * unitVector;

    sf::Vector2f newTangentialVector_1 = scalarTangential_1 * unitTangent;
    sf::Vector2f newTangentialVector_2 = scalarTangential_2 * unitTangent;

    sf::Vector2f finalVel1 = newNormalVelVector_1 + newTangentialVector_1;
    sf::Vector2f finalVel2 = newNormalVelVector_2 + newTangentialVector_2;

    //time for chaos
    if (distanceColl <= 0){
        position += unitVector * (distanceColl);
        objectB.position -= unitVector * (distanceColl);  
        velocity = finalVel1;
        objectB.velocity = finalVel2;
        //std::cout << normalVector.x << std::endl;
    }





}
