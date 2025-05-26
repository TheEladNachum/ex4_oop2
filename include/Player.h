#pragma once
#include "MovingObject.h"
#include <Board.h>

class Player : public MovingObject {
public:

	Player(const sf::Vector2u& startLocation, float speed, sf::Vector2u boardSize, int life);

	void movement(float deltaTime, sf::Keyboard::Key key = sf::Keyboard::Unknown) override;
	void updatePathOnBoard(Board& board);
	void clearTrail(Board& board);
	void resetToStart();

	int getLevel() const;
	void setLevel(int level);

	int getLife() const;
	void TakingLifeInOne();

private:
	sf::Vector2i m_direction = { 0, 0 };
	float m_timeSinceLastMove = 0.f;
	std::vector<sf::Vector2u> m_trail;
	int m_level = 1, m_life;

};