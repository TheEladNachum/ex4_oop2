#pragma once
#include "MovingObject.h"

class Enemy : public MovingObject {
public:
    Enemy(const std::vector<sf::Vector2u>& legalPositions, float speed);
    void movement(float deltaTime, sf::Keyboard::Key key = sf::Keyboard::Unknown) override;
};
