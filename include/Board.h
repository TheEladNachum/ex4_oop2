#pragma once
#include <SFML/Graphics.hpp>
#include "CellType.h"
#include "Constants.h"
#include <queue>
#include <vector>
#include <memory>

class Enemy;
class Board {
public:
    Board(sf::Vector2u windowSize, float cellSize, int borderThickness);
    void draw(sf::RenderWindow& window) const;

    CellType getCellType(const sf::Vector2u& gridPos) const;
    void setCell(const sf::Vector2u& gridPos, CellType type);

    sf::Vector2u getBoardSize() const;
    std::vector<sf::Vector2u> getLegalPositions() const;
    bool hasPathCells() const;


    void fillClosedArea(const std::vector<std::unique_ptr<Enemy>>& enemies); 



private:
    std::vector<std::vector<CellType>> m_board;
    float m_cellSize;
    int m_border;
    sf::Vector2u m_boardSize;

};