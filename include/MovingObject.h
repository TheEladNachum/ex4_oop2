#pragma once
#include <SFML/Graphics.hpp>

class MovingObject {

public:
    virtual void move(float deltaTime) = 0;
    MovingObject();
    virtual ~MovingObject() = default;
    void setLocation(const sf::Vector2i& loc);
    sf::Vector2i getLocation() const;

    sf::FloatRect getGlobalBounds() const;
    virtual void draw(sf::RenderTarget& target) const;  //virtual????

    //for game restart
    void setStartLocation(const sf::Vector2i& loc);
    sf::Vector2i getStartLocation();

    void setSpeed(int speed);
    int getSpeed() const;


private:
        int m_speed;
        sf::Vector2i m_startLocation;
        sf::Vector2i m_loc;
        sf::RectangleShape m_shape;
        int m_tileSize;
};    