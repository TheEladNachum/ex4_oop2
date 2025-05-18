#pragma once
#include <SFML/Graphics.hpp>
#include "CellType.h"

class Board {
public:
    Board(sf::Vector2u windowSize, float cellSize, int borderThickness);
    void draw(sf::RenderWindow& window) const;

    CellType getCellType(const sf::Vector2i& gridPos) const;
    void setCell(const sf::Vector2i& gridPos, CellType type);

private:
    std::vector<std::vector<CellType>> m_board;
    float m_cellSize;
    int m_border;
};