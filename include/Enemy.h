#pragma once
#include "MovingObject.h"

class Enemy : public MovingObject {
	public:
		void movement(float deltaTime, sf::Keyboard::Key key = sf::Keyboard::Unknown) override;
};
