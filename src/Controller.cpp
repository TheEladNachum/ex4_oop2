#include "Controller.h"
#include "board.h"
#include "CellType.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <random>
#include <set>



void Controller::run()  
{  
        sf::RenderWindow window(sf::VideoMode(1200, 800), "Xonix");
        try
        {
            Board board(window.getSize(), Constants::CELLSIZE, 1);

            Player player(sf::Vector2u(0, 0), 10, board.getBoardSize());
            sf::Clock clock;
            readLevelConfiguration(board);

            window.setFramerateLimit(60);
            sf::Keyboard::Key currentKey = sf::Keyboard::Unknown;


            //------------GAME LOOP--------------  
            while (window.isOpen())
            {
                float deltaTime = clock.restart().asSeconds();

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();

                    // Update direction only when a key is pressed  
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
                for (auto& enemy : m_enemies)
                {
                    enemy->updateTypeOnBoard(board);
                    enemy->movement(deltaTime, currentKey);
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
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            window.close();
        }

   return;  
}


void Controller::readLevelConfiguration(const Board& board)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    auto legalPositions = board.getLegalPositions();

    std::ifstream file("levels.txt");
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open levels.txt");
    }
    file >> m_passingPercentage;
    if (m_passingPercentage < 25 || m_passingPercentage > 95)
    {
        throw std::runtime_error("Invalid passing percentage in levels.txt");
    }
    int numOfEnemies = 0;
    file >> numOfEnemies;
    if (numOfEnemies < 0 || numOfEnemies > 100) 
    {
        throw std::runtime_error("Invalid number of enemies in levels.txt");
    }
	std::cout << "enemies: " << numOfEnemies << " m_passingPercentage: " << m_passingPercentage << std::endl; //debugging


    std::set<int> usedPositions;  
    int attempts = 0;
    int i = 0;

    while (i < numOfEnemies)
    {
        if (++attempts > 5000)
            throw std::runtime_error("Too many attempts to generate unique enemy positions");

        int index = std::rand() % legalPositions.size();
        sf::Vector2u pos = legalPositions[index];
        if (usedPositions.find(index) != usedPositions.end()) continue;
        else 
        {
			usedPositions.insert(index);
            m_enemies.emplace_back(std::make_unique<Enemy>(pos, 3.0f));
            ++i;
        }
    }
}


