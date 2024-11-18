#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Object.h"
#include "Spawn.h"
#include "Calculations.h"


int main()
{   
    sf::Vector2u window_size(1260u, 1260u);
    auto window = sf::RenderWindow({window_size.x, window_size.y}, "Gravity Sim");
      window.setFramerateLimit(144);

    sf::Vector2u centre(window_size.x/2,window_size.y/2);

    //std::vector<Object> planets = TwoBody();
    //std::vector<Object> planets = ThreeBody();
    std::vector<Object> planets = CentreMass();
    
    sf::Clock clock;
    while (window.isOpen()){
        for (auto event = sf::Event(); window.pollEvent(event);){
            if (event.type == sf::Event::Closed){
                window.close();
            }


            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            if (event.type == sf::Event::MouseWheelScrolled){  
                //std::cout << localPosition.x << std::endl;
                planets.emplace_back(5.f, sf::Color::Red);
                planets.back().setPosition(localPosition.x, localPosition.y);
                planets.back().initalVelocity(0,1);
                planets.back().objectMass(10.f);
                }
        }

        for (int i = 0; i < planets.size(); i++) {
            for (int j = (i+1); j < planets.size(); j++) {
                if (j != i){
                    //gravity with collisions enabled kinda janky
                    //planets[i].ElasticCollision(planets[j]);
                    GravForce(planets[i],planets[j]);
                }                                
            }
        }

        float dt = clock.restart().asSeconds();

        for (auto& planet : planets){
            planet.move();
            planet.boundaryCollision(window);  
       
        }
        window.clear();
        for (auto& planet : planets) {
            planet.draw(window);    
        }
        window.display();
    }
}

