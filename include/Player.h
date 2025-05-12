#pragma once
#include "MovingObject.h"

class Player : public MovingObject {
public:
	void move(float deltaTime) override;

};