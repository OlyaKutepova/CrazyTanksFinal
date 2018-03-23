#pragma once

#include <random>
#include "Direction.h"
#include "GameObject.h"
#include "Map.h"
#include "HealthUnderflowException.h"

class Tank : public GameObject
{
public:
	Tank(const COORD& Coordinates, int Health) : GameObject("EnemyTank", Coordinates), Dir(UP), Health(Health) {
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

	void MoveRand() {

		Dir = (Direction)(rand() + 1 % 4);

		Move();
	}

	void Shoot(){
		throw 2;
	}

	void TryToShoot() {
		throw 2;
	}

	
	Direction GetDir() const { return Dir; }


	const int& CheckHealth() {
		if (Health > 0)
			Health--;
		else
			throw HealthUnderflowException();
	}

	void SetAsPlayers() {
		SetTypeObject("Player");
	}
	void SetDirection(Direction Dir) {
		this->Dir = Dir;
	}
	void ReduseHealth() {
		if (Health > 0)
			Health--;
		else
			throw HealthUnderflowException();
	}

	bool operator==(const Tank& other) {
		if (other.GetCoordintes().X == this->GetCoordintes().X
			&& other.GetCoordintes().Y == this->GetCoordintes().Y)
			return true;
		else
			return false;	
	}
	
private:
	Direction Dir;
	int Health;
	};


	

