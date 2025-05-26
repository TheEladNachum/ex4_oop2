#include "Player.h"
#include "Constants.h"
#include <iostream>

Player::Player(const sf::Vector2u& startLocation, float speed, sf::Vector2u boardSize, int life)
{
    setStartLocation(startLocation);
    m_loc = startLocation;
    m_speed = speed;
    m_boardSize = boardSize;
    m_life = life;

    m_shape.setSize(sf::Vector2f(Constants::CELLSIZE, Constants::CELLSIZE));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition( static_cast<float>(m_loc.x * Constants::CELLSIZE), static_cast<float>(m_loc.y * Constants::CELLSIZE)
    );
}


void Player::movement(float deltaTime, sf::Keyboard::Key key)
{
    // עדכון כיוון תנועה רק אם נלחץ מקש חדש
    switch (key)
    {
    case sf::Keyboard::Up:    m_direction = { 0, -1 }; break;
    case sf::Keyboard::Down:  m_direction = { 0, 1 };  break;
    case sf::Keyboard::Left:  m_direction = { -1, 0 }; break;
    case sf::Keyboard::Right: m_direction = { 1, 0 };  break;
    default: break; // לא אפס את הכיוון – נמשיך לזוז בכיוון הנוכחי
    }

    // אין כיוון תנועה? עצור
    if (m_direction == sf::Vector2i(0, 0))
        return;

    // תזמון תנועה לפי מהירות
    m_timeSinceLastMove += deltaTime;
    float timePerStep = 0.2 / m_speed;

    if (m_timeSinceLastMove < timePerStep)
        return;

    // תזוזה למשבצת חדשה
    sf::Vector2i newPos = static_cast<sf::Vector2i>(m_loc) + m_direction;

    // בדיקת גבולות
    if (newPos.y < 0 || newPos.y >= static_cast<int>(m_boardSize.x)||
        newPos.x < 0 || newPos.x >= static_cast<int>(m_boardSize.y))
        return;

    // עדכון מיקום
    m_loc = static_cast<sf::Vector2u>(newPos);
    m_shape.setPosition(
        m_loc.x * Constants::CELLSIZE,
        m_loc.y * Constants::CELLSIZE
    );

    // אפס טיימר
    m_timeSinceLastMove = 0.f;
}

void Player::updatePathOnBoard(Board& board)
{
    if (board.getCellType(m_loc) == CellType::GROUND)
    {
        board.setCell(m_loc, CellType::PATH);
        m_trail.push_back(m_loc);  
    }
}

void Player::clearTrail(Board& board)
{
    for (const auto& cell : m_trail)
    {
        if (board.getCellType(cell) == CellType::PATH)
        {
            board.setCell(cell, CellType::GROUND);
        }
    }
    m_trail.clear();
}

void Player::resetToStart()
{
    m_loc = getStartLocation();
    m_shape.setPosition(
        m_loc.x * Constants::CELLSIZE,
        m_loc.y * Constants::CELLSIZE + Constants::MARGIN
    );
    m_direction = { 0, 0 };
    m_timeSinceLastMove = 0.f;
}

int Player::getLevel() const { return m_level; }
void Player::setLevel(int level) { m_level = level; }

int Player::getLife() const { return m_life; }
void Player::TakingLifeInOne() { --m_life; }
