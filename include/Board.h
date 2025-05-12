#pragma once
#include <SFML/Graphics.hpp>
#include "CellType.h"

class Board {
public:
    Board(sf::Vector2u windowSize, float cellSize, int borderThickness);
    void draw(sf::RenderWindow& window) const;

    CellType getCellType(int row, int col) const; 
    void setCell(int row, int col, CellType type); 

private:
    std::vector<std::vector<CellType>> m_board;
    float m_cellSize;
    int m_border;
};
