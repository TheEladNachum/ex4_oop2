#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MovingObject.h"
#include "Enemy.h"

class Controller {

	public:
		void run();

	private:
		std::vector<std::unique_ptr<Enemy>> m_movingObject;
		sf::Clock m_Clock;

};