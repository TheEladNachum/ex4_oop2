#include "Controller.h"
#include "board.h"
#include "CellType.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <random>
#include <set>

bool playerLost = false;

void Controller::run()  
{
    m_enemies;
        sf::RenderWindow window(sf::VideoMode(1200, 800), "Xonix");
        sf::Font font;
        try {
            font = loadFontOrThrow("arial.ttf");
        }
        catch (const std::exception& e) {
            std::cerr << "Font loading error: " << e.what() << std::endl;
            window.close();
            return;
        }

        try
        {
            Board board(window.getSize(), Constants::CELLSIZE, 1);
            Player player(sf::Vector2u(0, 0), 10, board.getBoardSize(), 3);
            sf::Clock clock;
            readLevelConfiguration(board);
            window.setFramerateLimit(60);
            sf::Keyboard::Key currentKey = sf::Keyboard::Unknown;


            //------------GAME LOOP--------------  
            while (window.isOpen())
            {
                sf::Text infoText = createInfoText(font, player, board.getBottomOfBoard());
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

                playerLost = false;
                playerLost = checkCollisions(player, board);

                if (!playerLost &&
                    board.getCellType(player.getLocation()) == CellType::WALL &&
                    board.hasPathCells())
                {
                    board.fillClosedArea(m_enemies);
                }
                if (board.getCoveredPercentage() >= m_passingPercentage)
                {
                    std::cout << "Level cleared! Moving to next stage." << std::endl;
                }


                if (playerLost && checkGameOver(player, board, window, font))
                {
                    return;
                }
               
                window.clear();
                board.draw(window);
                player.draw(window);
                for (const auto& enemy : m_enemies)
                {
                    enemy->draw(window);
                }
                window.draw(infoText);
                window.display();
            }
        }
        catch (const std::runtime_error& e)
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

bool Controller::checkCollisions(Player& player, Board& board)
{
    for (const auto& enemy : m_enemies)
    {
        if (player.getGlobalBounds().intersects(enemy->getGlobalBounds()))
        {
            std::cout << "PLAYER LOST! (collision)" << std::endl;
            player.clearTrail(board);
            player.TakingLifeInOne();
            player.resetToStart();
            return true;
        }
    }

    for (const auto& enemy : m_enemies)
    {
        if (board.getCellType(enemy->getLocation()) == CellType::PATH)
        {
            std::cout << "PLAYER LOST! (enemy touched path)" << std::endl;
            player.clearTrail(board);
            player.TakingLifeInOne();
            player.resetToStart();
            return true;
        }
    }

    return false;
}

bool Controller::checkGameOver(Player& player, Board& board, sf::RenderWindow& window, const sf::Font& font)
{
    if (player.getLife() <= 0)
    {
        sf::Text gameOverText("Game Over", font, 60);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(400, 300);

        window.clear();
        board.draw(window);
        player.draw(window);
        for (const auto& enemy : m_enemies)
            enemy->draw(window);
        window.draw(gameOverText);
        window.display();

        sf::sleep(sf::seconds(3));
        window.close();
        return true;
    }

    return false;
}

sf::Font Controller::loadFontOrThrow(const std::string& path)
{
    sf::Font font;
    if (!font.loadFromFile(path))
    {
        throw std::runtime_error("Failed to load font from file: " + path);
    }
    return font;
}

sf::Text Controller::createInfoText(const sf::Font& font, const Player& player, float boardBottom)
{
    sf::Text infoText;
    infoText.setFont(font);
    infoText.setString("Level: " + std::to_string(player.getLevel()) +
        "  Life: " + std::to_string(player.getLife()));
    infoText.setCharacterSize(26);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition(100.f, boardBottom - 40);
    return infoText;
}
