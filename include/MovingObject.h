#pragma once

#include "Object.h"

class MovingObject : public Object {

public:
    virtual void move(float deltaTime) = 0;

private:
        int m_speed;


};