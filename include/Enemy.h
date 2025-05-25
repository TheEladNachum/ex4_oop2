#pragma once
#include "MovingObject.h"
#include "CellType.h"
#include "Board.h"


class Enemy : public MovingObject {
public:
    //Enemy(const std::vector<sf::Vector2u>& legalPositions, float speed);
	Enemy(sf::Vector2u loc, float speed);

    void movement(float deltaTime, sf::Keyboard::Key key = sf::Keyboard::Unknown) override;
    void updateTypeOnBoard(Board& board);

private:
    sf::Vector2i m_direction;
	CellType m_nextCellType= CellType::GROUND;
	CellType m_nextXType = CellType::GROUND;
	CellType m_nextYType = CellType::GROUND;
	float m_timeSinceLastMove = 0.f;

};
