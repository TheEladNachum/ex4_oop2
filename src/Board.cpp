#include "Board.h"
#include "CellType.h"



Board::Board(sf::Vector2u windowSizeInPixels, int cellSize, int borderThickness)
    : m_tileSize(cellSize), m_border(borderThickness)
{
    int rows = static_cast<int>(windowSizeInPixels.y / cellSize);
    int cols = static_cast<int>(windowSizeInPixels.x / cellSize);

    m_board.resize(rows, std::vector<CellType>(cols, CellType::GROUND));

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            if (r < m_border || r >= rows - m_border ||
                c < m_border || c >= cols - m_border)
            {
                m_board[r][c] = CellType::WALL;
            }
        }
    }
}



void Board::draw(sf::RenderWindow& window) const
{
    sf::RectangleShape cellShape(sf::Vector2f((float)m_tileSize, (float)m_tileSize));

    for (int row = 0; row < m_board.size(); ++row)
    {
        for (int col = 0; col < m_board[row].size(); ++col)
        {
            cellShape.setPosition(
                static_cast<float>(col * m_tileSize),
                static_cast<float>(row * m_tileSize)
            );

            switch (m_board[row][col])
            {
            case CellType::GROUND: cellShape.setFillColor(sf::Color::Black); break;
            case CellType::WALL:   cellShape.setFillColor(sf::Color::Blue); break;
            case CellType::PATH:   cellShape.setFillColor(sf::Color::Magenta); break;
            default:               cellShape.setFillColor(sf::Color::Red); break;
            }

            window.draw(cellShape);
        }
    }
}


CellType Board::getCellType(const sf::Vector2i& gridPos) const
{
    int row = gridPos.y;
    int col = gridPos.x;

    if (row < 0 || row >= static_cast<int>(m_board.size()) ||
        col < 0 || col >= static_cast<int>(m_board[0].size()))
    {
        return CellType::WALL;
    }

    return m_board[row][col];
}

void Board::setCell(const sf::Vector2i& gridPos, CellType type)
{
    int row = gridPos.y;
    int col = gridPos.x;

    if (row < 0 || row >= static_cast<int>(m_board.size()) ||
        col < 0 || col >= static_cast<int>(m_board[0].size()))
    {
        return;
    }

    m_board[row][col] = type;
}

