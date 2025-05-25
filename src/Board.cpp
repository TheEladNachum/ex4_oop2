#include "Board.h"
#include "CellType.h"
#include "Enemy.h"


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
               case CellType::PATH:
                   cellShape.setFillColor(sf::Color::Magenta);
                   break;
            }

            // הוספת השוליים העליונים בציור
            cellShape.setPosition(col * m_cellSize, row * m_cellSize);
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

std::vector<sf::Vector2u> Board::getLegalPositions() const
{
    std::vector<sf::Vector2u> legalPositions;

    for (unsigned int row = m_border; row < m_boardSize.y - m_border; ++row)
    {
        for (unsigned int col = m_border; col < m_boardSize.x - m_border; ++col)
        {
            legalPositions.emplace_back(col, row);
        }
    }

    return legalPositions;
}


bool Board::hasPathCells() const
{
    for (const auto& row : m_board)
    {
        for (CellType cell : row)
        {
            if (cell == CellType::PATH)
                return true;
        }
    }
    return false;
}

void Board::fillClosedArea(const std::vector<std::unique_ptr<Enemy>>& enemies)
{
    const int rows = static_cast<int>(m_board.size());
    const int cols = static_cast<int>(m_board[0].size());

    std::vector<std::vector<bool>> globalVisited(rows, std::vector<bool>(cols, false));
    const int dx[4]{ -1,1,0,0 };
    const int dy[4]{ 0,0,-1,1 };

    std::vector<std::pair<int, int>> bestRegion;
    bool bestHasEnemy = false;
    bool foundRegion = false;

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (m_board[y][x] == CellType::PATH)
                for (int d = 0; d < 4; ++d)
                {
                    int sx = x + dx[d], sy = y + dy[d];
                    if (sx < 0 || sy < 0 || sx >= cols || sy >= rows)   continue;
                    if (m_board[sy][sx] != CellType::GROUND)            continue;
                    if (globalVisited[sy][sx])                          continue;

                    std::queue<std::pair<int, int>> q;
                    std::vector<std::pair<int, int>> region;
                    bool touchesBorder = false;
                    bool containsEnemy = false;

                    q.emplace(sx, sy);
                    globalVisited[sy][sx] = true;

                    while (!q.empty())
                    {
                        auto [cx, cy] = q.front(); q.pop();
                        region.emplace_back(cx, cy);

                        for (const auto& e : enemies)
                            if (e->getLocation() == sf::Vector2u(cx, cy))
                                containsEnemy = true;

                        for (int k = 0; k < 4; ++k)
                        {
                            int nx = cx + dx[k], ny = cy + dy[k];
                            if (nx < 0 || ny < 0 || nx >= cols || ny >= rows)
                            {
                                touchesBorder = true; continue;
                            }

                            if (globalVisited[ny][nx])                         continue;
                            if (m_board[ny][nx] != CellType::GROUND)           continue;

                            globalVisited[ny][nx] = true;
                            q.emplace(nx, ny);
                        }
                    }

                    if (!touchesBorder &&
                        (!foundRegion || region.size() < bestRegion.size()))
                    {
                        bestRegion = std::move(region);
                        bestHasEnemy = containsEnemy;
                        foundRegion = true;
                    }
                }

    if (foundRegion && !bestHasEnemy)
        for (auto [x, y] : bestRegion)
            m_board[y][x] = CellType::WALL;

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (m_board[y][x] == CellType::PATH)
                m_board[y][x] = CellType::WALL;
}
