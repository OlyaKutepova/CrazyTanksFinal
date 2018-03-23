#pragma once
#include "Direction.h"
#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall(const COORD& Coordinates, int Length) : GameObject("Wall", Coordinates), Dir(UP), Length(Length) { }

	const Direction& GetDirection() const {
		return Dir;
	}

	int  GetLength() const {
		return Length;
	}

	void SetDirecton(const Direction& Dir ) {
		this->Dir = Dir;
		}

	void SetLenght(const int& Lenght ) {
		this->Length = Length;
	}
private:
	Direction Dir;
	int Length;


};