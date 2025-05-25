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
    Board board(window.getSize(), Constants::CELLSIZE, 1);

    Player player(sf::Vector2u(0,2 ),10, board.getBoardSize());
    auto legalPositions = board.getLegalPositions();
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    m_enemies.push_back(std::make_unique<Enemy>(legalPositions, 3.0f));
    sf::Clock clock;

    window.setFramerateLimit(60);
    sf::Keyboard::Key currentKey = sf::Keyboard::Unknown;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // עידכון הכיוון רק כשנלחץ מקש
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up ||
                    event.key.code == sf::Keyboard::Down ||
                    event.key.code == sf::Keyboard::Left ||
                    event.key.code == sf::Keyboard::Right)
                {
                    currentKey = event.key.code;
                }
            }
        }

        player.movement(deltaTime, currentKey);
        player.updatePathOnBoard(board);

        bool playerLost = false;

        for (const auto& enemy : m_enemies)
        {
            if (player.getGlobalBounds().intersects(enemy->getGlobalBounds()))
            {
                std::cout << "PLAYER LOST! (collision)" << std::endl;
                playerLost = true;
                player.clearTrail(board);
                player.resetToStart();
                break;
            }
        }

        if (!playerLost)
        {
            for (const auto& enemy : m_enemies)
            {
                if (board.getCellType(enemy->getLocation()) == CellType::PATH)
                {
                    std::cout << "PLAYER LOST! (enemy touched path)" << std::endl;
                    playerLost = true;
                    player.clearTrail(board);
                    player.resetToStart();
                    break;
                }
            }
        }

        if (!playerLost &&
            board.getCellType(player.getLocation()) == CellType::WALL &&
            board.hasPathCells())
        {
            board.fillClosedArea(m_enemies);
        }



        window.clear();
        board.draw(window);
        player.draw(window);
        for (const auto& enemy : m_enemies)
        {
            enemy->draw(window);
        }
        window.display();
    }


    return;
}