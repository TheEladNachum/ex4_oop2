#pragma once
#include "MovingObject.h"

class Enemy : public MovingObject {
	public:
		void move(float deltaTime) override;
};
