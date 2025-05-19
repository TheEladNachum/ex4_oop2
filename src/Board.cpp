#include "Board.h"
#include "CellType.h"



//Board::Board(sf::Vector2u windowSize, float cellSize, int borderThickness)
//    : m_cellSize(cellSize), m_border(borderThickness)
//{
//    int rows = static_cast<int>(windowSize.y / cellSize);
//    int cols = static_cast<int>(windowSize.x / cellSize);
//
//    m_board.resize(rows, std::vector<CellType>(cols, CellType::GROUND));
//
//    // set frame
//    for (int r = 0; r < rows; ++r)
//    {
//        for (int c = 0; c < cols; ++c)
//        {
//            if (r < m_border || r >= rows - m_border ||
//                c < m_border || c >= cols - m_border)
//            {
//                m_board[r][c] = CellType::WALL;
//            }
//        }
//    }
//}
//
//
//
//void Board::draw(sf::RenderWindow& window) const
//{
//    sf::RectangleShape cellShape(sf::Vector2f(m_cellSize, m_cellSize));
//
//    for (int row = 0; row < static_cast<int>(m_board.size()); ++row)
//    {
//        for (int col = 0; col < static_cast<int>(m_board[row].size()); ++col)
//        {
//            cellShape.setPosition(col * m_cellSize, row * m_cellSize);
//
//            switch (m_board[row][col])
//            {
//            case CellType::GROUND:
//                cellShape.setFillColor(sf::Color::Black);
//                break;
//
//            case CellType::WALL:
//                cellShape.setFillColor(sf::Color::Blue);
//                break;
//
//            case CellType::PATH:
//                cellShape.setFillColor(sf::Color::Magenta);
//                break;
//
//            default:
//                cellShape.setFillColor(sf::Color::Red); // fallback
//                break;
//            }
//
//            window.draw(cellShape);
//        }
//    }
//}

Board::Board(sf::Vector2u windowSize, float cellSize, int borderThickness)
    : m_cellSize(cellSize), m_border(borderThickness)
{

    int rows = static_cast<int>((windowSize.y - Constants::MARGIN) / cellSize);
    int cols = static_cast<int>(windowSize.x / cellSize);

    //update size
    m_boardSize.x = static_cast<unsigned int>(rows);
    m_boardSize.y = static_cast<unsigned int>(cols);

    m_board.resize(rows, std::vector<CellType>(cols, CellType::GROUND));

    // set frame
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
    sf::RectangleShape cellShape(sf::Vector2f(m_cellSize, m_cellSize));
    const float offsetY = 2 * m_cellSize; // השוליים העליונים

    for (int row = 0; row < static_cast<int>(m_board.size()); ++row)
    {
        for (int col = 0; col < static_cast<int>(m_board[row].size()); ++col)
        {
            switch (m_board[row][col])
            {
            case CellType::GROUND:
                cellShape.setFillColor(sf::Color::Black);
                break;
            case CellType::WALL:
                cellShape.setFillColor(sf::Color::Blue);
                break;
            }

            // הוספת השוליים העליונים בציור
            cellShape.setPosition(col * m_cellSize, row * m_cellSize + offsetY);
            window.draw(cellShape);
        }
    }
}


CellType Board::getCellType(const sf::Vector2u& gridPos) const
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

void Board::setCell(const sf::Vector2u& gridPos, CellType type)
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

sf::Vector2u Board::getBoardSize() const
{
    return m_boardSize;
}

