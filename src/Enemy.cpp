#include "Enemy.h"
#include <iostream>
#include "Constants.h"
#include <cstdlib>
#include <ctime>


void Enemy::movement(float deltaTime, sf::Keyboard::Key)
{
    m_timeSinceLastMove += deltaTime;

    float timePerStep = 0.2f / m_speed;
    if (m_timeSinceLastMove < timePerStep)
        return;

    m_timeSinceLastMove = 0.f;

    if (m_nextCellType != CellType::WALL)
    {
        m_loc = static_cast<sf::Vector2u>(static_cast<sf::Vector2i>(m_loc) + m_direction);
        m_shape.setPosition(
            m_loc.x * Constants::CELLSIZE,
            m_loc.y * Constants::CELLSIZE
        );
        return;
    }

    if (m_nextXType == CellType::WALL)
        m_direction.x *= -1;

    if (m_nextYType == CellType::WALL)
        m_direction.y *= -1;

    
}


Enemy::Enemy(sf::Vector2u loc, float speed)
{
    m_speed = speed;
    m_loc = loc;

    m_shape.setSize(sf::Vector2f(Constants::CELLSIZE, Constants::CELLSIZE));
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(
        m_loc.x * Constants::CELLSIZE,
        m_loc.y * Constants::CELLSIZE + Constants::MARGIN
    );


    int dx[] = { 1, -1 };
    int dy[] = { 1, -1 };
    m_direction = { dx[std::rand() % 2], dy[std::rand() % 2] };
    //m_direction = { 1, -1 };

}


void Enemy::updateTypeOnBoard(Board& board)
{
    sf::Vector2i curr = static_cast<sf::Vector2i>(m_loc);
    sf::Vector2i next = curr + m_direction;
    sf::Vector2i nextX = curr + sf::Vector2i(m_direction.x, 0);
    sf::Vector2i nextY = curr + sf::Vector2i(0, m_direction.y);

    m_nextCellType = board.getCellType(static_cast<sf::Vector2u>(next));
    m_nextXType = board.getCellType(static_cast<sf::Vector2u>(nextX));
    m_nextYType = board.getCellType(static_cast<sf::Vector2u>(nextY));

    // זהה לפונקציה של החבר: שינוי כיוון לפי פגיעות
    if (m_nextYType == CellType::WALL)
        m_direction.y *= -1;

    if (m_nextXType == CellType::WALL)
        m_direction.x *= -1;
}

