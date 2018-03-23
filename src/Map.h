#pragma once
#include <iostream>
#include "MapOverflowException.h"
#include "Gold.h"
#include "BreakableWall.h"
#include <vector>
#include "Bullet.h"
#include <Windows.h>
#include "Tank.h"



class Map
{
public:
	Map(int MapSize, int TankCount) : 
		MapSize(MapSize), 
		TankCount(TankCount), Score(0), Time(0), 
		PlayerTank(Tank({MapSize - 4, MapSize / 2})),
		gold({MapSize - 2, MapSize / 2})
	{
		COORD TankCoords = { (rand() + 1 % 2), (rand() + 1 % 3) };
		handle = GetStdHandle(STD_OUTPUT_HANDLE);

		for (int i = 0; i < TankCount; i++) {

			TankCoords.Y += rand() + 1 % 3;
			if (TankCoords.Y >= MapSize - 1) {
				TankCoords.Y = rand() + 1 % 3;
				TankCoords.X += rand() + 1 % 3;
				if (TankCoords.X >= MapSize - 1)
					throw MapOverflowException();
			}

			TankVector.push_back(Tank(TankCoords));
		}

		int ForwardCounter = -1;
		for (int i = 0; i < (MapSize - 2) / 2; i++) {
			COORD pos = {(rand() + 1 % MapSize - 4), (rand() + 1 % 2) + (i * 2)};
			int length = rand() + 2 % 3;

			WallVector.push_back(BreakableWall(pos, length));

			pos = { (rand() + 1 % MapSize - 4), (rand() + 1 % 2) + (i * 2) };
			length = rand() + 2 % 3;

			WallVector.push_back(BreakableWall(pos, length));
			ForwardCounter += 2;
			WallVector[ForwardCounter].SetDirecton(RIGHT);
		}
	}
	
	void Draw() const {
		system("cls");
		//Отрисовка границ поля:
		for (int i = 0; i < MapSize; i++) {
			for (int j = 0; j < MapSize; j++)
				if (i == 0 || j == 0 || i == MapSize || j == MapSize)
					std::cout << "#";
			std::cout << std::endl;
		}

		//Отрисовка объектов + проверки коллизий
	}
	
	void Refresh();
	void AnswerKey();
	void CountTime();
	void DeleteBullet(Bullet* bul);

private:
	std::vector<Tank> TankVector;
	std::vector<BreakableWall> WallVector;
	std::vector<Bullet> BulletVector;
	Tank PlayerTank;
	Gold gold;
	HANDLE handle;
	int Score;
	int Time;
	const int MapSize;
	int TankCount;

	GameObject* CheckCollision(GameObject* obj) {
		for (Tank item : TankVector) {
			if (item.GetCoordintes().X == obj->GetCoordintes().X
				&& item.GetCoordintes().Y == obj->GetCoordintes().Y
				&& &item != obj) {
				return &item;
			}
		}
		for (BreakableWall item : WallVector) {
			if (item.GetCoordintes().X == obj->GetCoordintes().X
				&& item.GetCoordintes().Y == obj->GetCoordintes().Y) {
				return &item;
			}
		}
		for (Bullet item : BulletVector) {
			if (item.GetCoordintes().X == obj->GetCoordintes().X
				&& item.GetCoordintes().Y == obj->GetCoordintes().Y
				&& &item != obj) {
				return &item;
			}
		}

		return nullptr;
	}

	void SolveCollision(GameObject* obj, GameObject* col) {
		std::string type = obj->GetType();
		std::string col_type = col->GetType();
		if (type == "EnemyTank") {
			Tank* work_obj = (Tank*)obj;
			
			if (col_type == "EnemyTank") {
				int vectorX = 0;
				int vectorY = 0;

				switch (work_obj->GetDir()) {
				case UP:
					vectorX = 1;
					break;
				case DOWN:
					vectorX = -1;
					break;
				case RIGHT:
					vectorY = -1;
					break;
				case LEFT:
					vectorY = 1;
					break;
				}

				work_obj->SetCoordinates({(work_obj->GetCoordintes().X + vectorX),
					(work_obj->GetCoordintes().Y + vectorY) });
			}
			else if (col_type == "Bullet") {
				if (((Bullet*)col)->IsPlayers()) {
					work_obj->ReduseHealth();
					DeleteBullet((Bullet*)col);
				}
				else {
					DeleteBullet((Bullet*)col);
				}
			}
			else if (col_type == "BreakableWall" || col_type == "Wall") {
				int vectorX = 0;
				int vectorY = 0;

				switch (work_obj->GetDir()) {
				case UP:
					vectorX = 1;
					break;
				case DOWN:
					vectorX = -1;
					break;
				case RIGHT:
					vectorY = -1;
					break;
				case LEFT:
					vectorY = 1;
					break;
				}

				work_obj->SetCoordinates({ (work_obj->GetCoordintes().X + vectorX),
					(work_obj->GetCoordintes().Y + vectorY) });
			}
			else if (col_type == "Player") {
				int vectorX = 0;
				int vectorY = 0;

				switch (work_obj->GetDir()) {
				case UP:
					vectorX = 1;
					break;
				case DOWN:
					vectorX = -1;
					break;
				case RIGHT:
					vectorY = -1;
					break;
				case LEFT:
					vectorY = 1;
					break;
				}

				work_obj->SetCoordinates({ (work_obj->GetCoordintes().X + vectorX),
					(work_obj->GetCoordintes().Y + vectorY) });
			}
			else if (col_type == "Gold") {
				((Gold*)col)->ReduseHealth();
			}
		}
		else if (type == "Bullet") {
			Bullet* work_obj = (Bullet*)obj;

			if (col_type == "EnemyTank") {
				if (work_obj->IsPlayers()) {
					((Tank*)col)->ReduseHealth();
					DeleteBullet(work_obj);
				}
				else {
					DeleteBullet(work_obj);
				}
			}
			else if (col_type == "Bullet" || col_type == "Wall") {
				DeleteBullet(work_obj);
			}
			else if (col_type == "BreakableWall") {
				((BreakableWall*)col)->ReduseHealth();
				DeleteBullet(work_obj);
			}
			else if (col_type == "Player") {
				if (work_obj->IsPlayers()) {
					DeleteBullet(work_obj);
				}
				else {
					((Tank*)col)->ReduseHealth();
					DeleteBullet(work_obj);
				}
			}
			else if (col_type == "Gold") {
				((Gold*)col)->ReduseHealth();
				DeleteBullet(work_obj);
			}
		}
		else if (type == "Player") {
			Tank* work_obj = (Tank*)obj;

			if (col_type == "EnemyTank") {
				int vectorX = 0;
				int vectorY = 0;

				switch (work_obj->GetDir()) {
				case UP:
					vectorX = 1;
					break;
				case DOWN:
					vectorX = -1;
					break;
				case RIGHT:
					vectorY = -1;
					break;
				case LEFT:
					vectorY = 1;
					break;
				}

				work_obj->SetCoordinates({ (work_obj->GetCoordintes().X + vectorX),
					(work_obj->GetCoordintes().Y + vectorY) });
			}
			else if (col_type == "Bullet") {
				if (!(((Bullet*)col)->IsPlayers())) {
					work_obj->ReduseHealth();
					DeleteBullet((Bullet*)col);
				}
				else {
					DeleteBullet((Bullet*)col);
				}
			}
			else if (col_type == "BreakableWall" || col_type == "Wall") {
				int vectorX = 0;
				int vectorY = 0;

				switch (work_obj->GetDir()) {
				case UP:
					vectorX = 1;
					break;
				case DOWN:
					vectorX = -1;
					break;
				case RIGHT:
					vectorY = -1;
					break;
				case LEFT:
					vectorY = 1;
					break;
				}

				work_obj->SetCoordinates({ (work_obj->GetCoordintes().X + vectorX),
					(work_obj->GetCoordintes().Y + vectorY) });
			}
			else if (col_type == "Gold") {
				((Gold*)col)->ReduseHealth();
			}
		}
	}
};

