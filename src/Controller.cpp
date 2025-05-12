#include "Controller.h"
#include "Player.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>


void Controller::run()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Xonix");
    Player player;

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(EXIT_SUCCESS);
            }
        }

        //player movement
        for (sf::Keyboard::Key key : {sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Down})
        {
            if (sf::Keyboard::isKeyPressed(key)) {
                player.move(0.0);
            }
        }
  
        //update enemy movement 
        for (auto& obj : m_movingObject)
        {
            obj->move(0.0);
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return;
}