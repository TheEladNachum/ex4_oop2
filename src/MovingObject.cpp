#include "MovingObject.h"

MovingObject::MovingObject() {}

void MovingObject::setStartLocation(const sf::Vector2i& loc) { m_startLocation = loc; }
sf::Vector2i MovingObject::getStartLocation() { return m_startLocation; }

void MovingObject::setLocation(const sf::Vector2i& loc) { m_loc = loc; }
sf::Vector2i MovingObject::getLocation() const { return m_loc; }

void MovingObject::draw(sf::RenderTarget& target) const
{
    //m_shape.setPosition(m_loc.x, m_loc.y);
    target.draw(m_shape);
}

sf::FloatRect MovingObject::getGlobalBounds() const {
    return m_shape.getGlobalBounds();
}

void MovingObject::setSpeed(int speed)
{
    m_speed = speed;
}

int MovingObject::getSpeed() const
{
    return m_speed;
}
