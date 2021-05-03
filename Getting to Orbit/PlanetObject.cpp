#include "gettingToOrbit.h"
#include <iostream>

// Planet constructor
GettingToOrbit::Planet::Planet(float radius, double mass, sf::Color color, std::string name)
{
    _radius = radius;
    _planet.setOrigin({radius, radius});
    _mass = mass;
    _name = name;
    _planet.setRadius(radius);
    _planet.setFillColor(color);

    _velocity = { 0, 0 };
    _acceleration = { 0, 0 };
}

// Setting the position with its origin
void GettingToOrbit::Planet::setPosition(float x, float y)
{
    _position = { x, y };
}

void GettingToOrbit::Planet::setVelocity(float x, float y)
{
    _velocity = { x, y };
}

sf::Vector2f GettingToOrbit::Planet::getPosition() const
{
   return _position; 
}

double GettingToOrbit::Planet::getMass() const
{
    return _mass;
}

float GettingToOrbit::Planet::getRadius() const
{
    return _radius;
}

void GettingToOrbit::Planet::updateAcceleration(std::vector<Planet*> planets)
{
    sf::Vector2f distance;
    float totalDistance;

    for (Planet* planet : planets)
    {
        if (planet != this)
        {
            distance = calculateDistanceBetweenPlanets(*planet, *this);
            totalDistance = calculateDistanceBetweenPlanetsF(*planet, *this);
            if (distance.x != 0)
                _acceleration.x += (float)((planet->getMass() / pow(totalDistance, 2)) * (distance.x / totalDistance));
            if (distance.y != 0)
                _acceleration.y += (float)((planet->getMass() / pow(totalDistance, 2)) * (distance.y / totalDistance));
            if (checkCollision(*planet, *this))
            {
                _acceleration = { 0, 0 };
                _velocity = -(sf::Vector2f{ _velocity.x, _velocity.y});
            }
        }
    }
}

// drawing the object
void GettingToOrbit::Planet::update(sf::RenderWindow& window, sf::Time dT)
{
    _velocity.x += _acceleration.x * dT.asSeconds();
    _velocity.y += _acceleration.y * dT.asSeconds();
    _position.x += _velocity.x * dT.asSeconds();
    _position.y += _velocity.y * dT.asSeconds();
    _planet.setPosition(_position);
    _acceleration = { 0, 0 };
    window.draw(_planet);
}

sf::Vector2f GettingToOrbit::calculateDistanceBetweenPlanets(Planet& a, Planet& b)
{
    return a.getPosition() - b.getPosition();
}

float GettingToOrbit::calculateDistanceBetweenPlanetsF(Planet& a, Planet& b)
{
    sf::Vector2f distance = calculateDistanceBetweenPlanets(a, b);
    float distanceF = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
    return distanceF;
}

bool GettingToOrbit::checkCollision(Planet& a, Planet& b)
{
    sf::Vector2f distance = calculateDistanceBetweenPlanets(a, b);
    float totalRadiusDistance = a.getRadius() + b.getRadius();
    float distanceF = sqrt(pow(distance.x, 2) + pow(distance.y, 2));

    if (distanceF <= totalRadiusDistance) return true;
    return false;
}