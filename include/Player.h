#pragma once
#include "MovingObject.h"
#include <Board.h>

class Player : public MovingObject {
public:

	Player(const sf::Vector2u& startLocation, float speed, sf::Vector2u boardSize);

	void movement(float deltaTime, sf::Keyboard::Key key) override;
	void updatePathOnBoard(Board& board);
	void clearTrail(Board& board);
	void resetToStart();


private:
	sf::Vector2i m_direction = { 0, 0 };
	float m_timeSinceLastMove = 0.f;
	std::vector<sf::Vector2u> m_trail;  // שביל תאים שציירנו (PATH)

};