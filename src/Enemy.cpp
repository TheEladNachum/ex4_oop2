#include "Enemy.h"
#include <iostream>
#include "Constants.h"
#include <cstdlib>
#include <ctime>


void Enemy::movement(float deltaTime, sf::Keyboard::Key key)
{
	std::cout << "enemy Moving" << std::endl;
}

Enemy::Enemy(const std::vector<sf::Vector2u>& legalPositions, float speed)
{
    m_speed = speed;

    static bool initialized = false;
    if (!initialized) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        initialized = true;
    }

    if (legalPositions.empty())
        throw std::runtime_error("No legal positions to place enemy!");

    // בוחר מיקום אקראי מתוך הרשימה
    m_loc = legalPositions[std::rand() % legalPositions.size()];

    m_shape.setSize(sf::Vector2f(Constants::CELLSIZE, Constants::CELLSIZE));
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(
        m_loc.x * Constants::CELLSIZE,
        m_loc.y * Constants::CELLSIZE + Constants::MARGIN
    );
}


