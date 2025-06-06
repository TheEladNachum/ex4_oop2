#include "Player.h"
#include "Constants.h"
#include <iostream>

Player::Player(const sf::Vector2u& startLocation, float speed, sf::Vector2u boardSize)
{
    setStartLocation(startLocation);
    m_loc = startLocation;
    m_speed = speed;
    m_boardSize = boardSize;

    m_shape.setSize(sf::Vector2f(Constants::CELLSIZE, Constants::CELLSIZE));
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition( static_cast<float>(m_loc.x * Constants::CELLSIZE), static_cast<float>(m_loc.y * Constants::CELLSIZE)
    );
}


void Player::movement(float deltaTime, sf::Keyboard::Key key)
{
    // ����� ����� ����� �� �� ���� ��� ���
    switch (key)
    {
    case sf::Keyboard::Up:    m_direction = { 0, -1 }; break;
    case sf::Keyboard::Down:  m_direction = { 0, 1 };  break;
    case sf::Keyboard::Left:  m_direction = { -1, 0 }; break;
    case sf::Keyboard::Right: m_direction = { 1, 0 };  break;
    default: break; // �� ��� �� ������ � ����� ���� ������ ������
    }

    // ��� ����� �����? ����
    if (m_direction == sf::Vector2i(0, 0))
        return;

    // ����� ����� ��� ������
    m_timeSinceLastMove += deltaTime;
    float timePerStep = 0.2 / m_speed;

    if (m_timeSinceLastMove < timePerStep)
        return;

    // ����� ������ ����
    sf::Vector2i newPos = static_cast<sf::Vector2i>(m_loc) + m_direction;

    // ����� ������
    if (newPos.y < 0 || newPos.y >= static_cast<int>(m_boardSize.x)||
        newPos.x < 0 || newPos.x >= static_cast<int>(m_boardSize.y))
        return;

    // ����� �����
    m_loc = static_cast<sf::Vector2u>(newPos);
    m_shape.setPosition(
        m_loc.x * Constants::CELLSIZE,
        m_loc.y * Constants::CELLSIZE + Constants::MARGIN
    );

    // ��� �����
    m_timeSinceLastMove = 0.f;
}



