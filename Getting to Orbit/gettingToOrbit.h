#ifndef GETTING_TO_ORBIT_H
#define GETTING_TO_ORBIT_G

#include <vector>
#include <cmath>

#include "libs\imgui.h"
#include "libs\imgui-sfml.h"

#include <sfml/graphics.hpp>


namespace GettingToOrbit
{
    
    class Planet
    {
    private:
        sf::CircleShape _planet;
        std::string _name;
        sf::Vector2f _position;
        sf::Vector2f _velocity;
        sf::Vector2f _acceleration;
        double _mass;
        float _radius;

    public:
        Planet(float radius, double mass, sf::Color, std::string name);
        void setPosition(float x, float y);
        void setVelocity(float x, float y);
        sf::Vector2f getPosition() const;
        double getMass() const;
        float getRadius() const;
        void updateAcceleration(std::vector<Planet*> planets);
        void update(sf::RenderWindow& window, sf::Time dT);
    };

    sf::Vector2f calculateDistanceBetweenPlanets(Planet& a, Planet& b);
    float calculateDistanceBetweenPlanetsF(Planet& a, Planet& b);
    bool checkCollision(Planet& a, Planet& b);
}



#endif // !GETTING_TO_ORBIT_H

