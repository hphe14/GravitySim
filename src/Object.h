#pragma once
#include <SFML/Graphics.hpp>

class Object {
public:
    
    Object(float radius, const sf::Color& color);


    sf::Vector2f getPosition();
    float getRadius() const;
    float objectMass(float m);
    float getMass();
    
    void setPosition(float x, float y);
    void setAcceleration(sf::Vector2f a);


    void draw(sf::RenderWindow& window) const;
    void initalVelocity(float vx, float vy);
    void move();


    void boundaryCollision(sf::RenderWindow& windowSize);
    void ElasticCollision(Object& objectB);
    


private:
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
     
};
