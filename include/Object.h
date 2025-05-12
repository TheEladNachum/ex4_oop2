#pragma once
#include <SFML/Graphics.hpp>

class Object {

public:
    Object();
    virtual ~Object() = default;

    void setLocation(const sf::Vector2f& loc);
    sf::Vector2f getLocation() const;

    sf::FloatRect getGlobalBounds() const;
    virtual void draw(sf::RenderTarget& target) const;  //virtual????

    //for game restart
    void setStartLocation(const sf::Vector2f& loc);

    sf::Vector2f getStartLocation();

private:
    sf::Vector2f m_startLocation;
    sf::Vector2f m_loc;
    sf::RectangleShape m_shape; 
    int m_tileSize;

};