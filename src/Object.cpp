#include "Object.h"

Object::Object() {}

void Object::setStartLocation(const sf::Vector2f& loc) { m_startLocation = loc; }
sf::Vector2f Object::getStartLocation() { return m_startLocation; }

void Object::setLocation(const sf::Vector2f& loc) { m_loc = loc; }
sf::Vector2f Object::getLocation() const { return m_loc; }

void Object::draw(sf::RenderTarget& target) const
{
    //m_shape.setPosition(m_loc.x, m_loc.y);
    target.draw(m_shape);
}

sf::FloatRect Object::getGlobalBounds() const {
    return m_shape.getGlobalBounds();
}