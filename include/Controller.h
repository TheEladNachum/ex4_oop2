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
		float m_passingPercentage = 0;
		sf::Clock m_Clock;

		void readLevelConfiguration(const Board& board);
		bool checkCollisions(Player& player, Board& board);
		bool checkGameOver(Player& player, Board& board, sf::RenderWindow& window, const sf::Font& font);
		sf::Font loadFontOrThrow(const std::string& path);
		sf::Text createInfoText(const sf::Font& font, const Player& player, float boardBottom);

};