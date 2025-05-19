#pragma once
#include "MovingObject.h"

class Player : public MovingObject {
public:

	Player(const sf::Vector2u& startLocation, float speed, sf::Vector2u boardSize);

	void movement(float deltaTime, sf::Keyboard::Key key) override;

private:
	sf::Vector2i m_direction = { 0, 0 };     // ����� ������ ������
	float m_timeSinceLastMove = 0.f;         // ��� ������


};