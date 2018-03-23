#pragma once
#include "Direction.h"
#include"GameObject.h"

class Bullet : public GameObject
{

public:
	Bullet(const COORD& Coordinates, const Direction& Dir, const bool& isPlayer = false) : GameObject("Bullet", Coordinates), Dir(Dir), isPlayer(isPlayer) {
	}
	
	void Move() {
		int VectorX = 0;
		int VectorY = 0;
		COORD crd = GetCoordintes();

		switch (Dir) {
		case UP:
			VectorX = -1;
			break;

		case DOWN:
			VectorX = 1;
			break;

		case RIGHT:
			VectorY = 1;
			break;

		case LEFT:
			VectorY = -1;
			break;
		}

		crd.X += VectorX;
		crd.Y += VectorY;
		SetCoordinates(crd);
	}
	bool IsPlayers() const {
		return isPlayer;
	}
	
private:
	Direction Dir;
	bool isPlayer;
};

