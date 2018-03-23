#pragma once
#include <string>
#include <Windows.h>

class GameObject
{
public:
	GameObject(const std::string& type) : TypeObject(type) {
		Coordinates = { 0, 0 };
	}
	GameObject(const std::string& type, COORD Coordinates) : TypeObject(type), Coordinates(Coordinates) { }

	void SetTypeObject(const std::string& type) {
		TypeObject = type;
	}
	const std::string& GetType() {
		return TypeObject;
	}
	void SetCoordinates(const COORD& crd) {
		Coordinates = crd;
	}
	const COORD& GetCoordintes() const {
		return Coordinates;
	}
	virtual ~GameObject() = 0;
private:
	std::string TypeObject;
	COORD Coordinates;
};

