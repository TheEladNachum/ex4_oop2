#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class MovingObject {

public:
    virtual void movement(float deltaTime, sf::Keyboard::Key key = sf::Keyboard::Unknown) = 0;
    MovingObject() = default;
    virtual ~MovingObject() = default;
    void setLocation(const sf::Vector2u& loc);
    sf::Vector2u getLocation() const;

    sf::FloatRect getGlobalBounds() const;
    virtual void draw(sf::RenderTarget& target) const;  //virtual????

    //for game restart
    void setStartLocation(const sf::Vector2u& loc);
    sf::Vector2u getStartLocation() const;

    void setSpeed(float speed);
    int getSpeed() const;

protected:
        float m_speed; 
        sf::RectangleShape m_shape;
        sf::Vector2u m_loc;
        sf::Vector2u m_boardSize;

private:
        sf::Vector2u m_startLocation;
        int m_tileSize;

};    