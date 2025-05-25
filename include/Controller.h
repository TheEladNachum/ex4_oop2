#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MovingObject.h"
#include "Enemy.h"
#include "Player.h"


class Controller {

	public:
		void run();

	private:
		std::vector<std::unique_ptr<Enemy>> m_enemies;
		int m_passingPercentage = 0;
		sf::Clock m_Clock;

		void readLevelConfiguration(const Board& board);
};