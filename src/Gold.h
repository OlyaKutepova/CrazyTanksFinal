#pragma once
#include "Direction.h"
#include "GameObject.h"
#include "HealthUnderflowException.h"

class Gold : public GameObject
{
public:
	Gold(const COORD& Coordinates) : GameObject("Gold", Coordinates) {
		Health = 1;
	}

	const int CheckHealth() {
		return Health;
	}
	void ReduseHealth() {
		if (Health > 0)
			Health--;
		else
			throw HealthUnderflowException();
	}

private:
	int Health;
};