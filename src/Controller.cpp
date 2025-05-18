#include "Controller.h"
#include "Player.h"
#include "Enemy.h"
#include "board.h"
#include "CellType.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>


void Controller::run()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Xonix");
    Player player;
    Board board(window.getSize(), Constants::CELLSIZE, 1);
    sf::Clock clock;

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
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
                player.move(deltaTime);
            }
        }
  
        //update enemy movement 
        for (auto& obj : m_movingObject)
        {
            obj->move(deltaTime);
        }

        window.clear(sf::Color::Black);
        board.draw(window);
        window.display();
    }

    return;
}