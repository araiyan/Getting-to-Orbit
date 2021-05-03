#include "gettingToOrbit.h"
#include <iostream>

#include <SFML/Graphics.hpp>

int main()
{
    GettingToOrbit::Planet earth(50, 59500000, sf::Color::Green, "Earth");
    GettingToOrbit::Planet moon(7, 73500, sf::Color::Blue, "Moon");
    GettingToOrbit::Planet astroid(3, 4000, sf::Color::Red, "Astroid");
    GettingToOrbit::Planet astroid2(2, 3000, sf::Color::Red, "Astroid2");

    std::vector<GettingToOrbit::Planet*> planets;

    earth.setPosition(400, 200);
    moon.setPosition(700, 700);
    astroid.setPosition(900, 300);
    astroid2.setPosition(500, 900);
    
    moon.setVelocity(-200 , 0);
    astroid.setVelocity(-50, 150);
    astroid2.setVelocity(100, -200);

    planets.emplace_back(&earth);
    planets.emplace_back(&moon);
    planets.emplace_back(&astroid);
    planets.emplace_back(&astroid2);

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Getting to Orbit!");

    sf::Clock deltaClock;
    sf::Time dT;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        dT = deltaClock.restart();

        for (GettingToOrbit::Planet* planet : planets)
        {
            planet->updateAcceleration(planets);
        }
       

        window.clear();
        for (GettingToOrbit::Planet* planet : planets)
        {
            planet->update(window, dT);
        }
        window.display();
    }

    return 0;
}