#pragma once
#include "Wall.h"
#include "HealthUnderflowException.h"

class BreakableWall : public Wall
{
public:
	BreakableWall(const COORD& Coordinates, int Length) : Wall(Coordinates, Length), Health(1) {
		SetTypeObject("BreakableWall");
	}
	const int& CheckHealth() const {
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

