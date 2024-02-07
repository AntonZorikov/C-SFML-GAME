#include <iostream>
#include <math.h>

class Person {
public:
	int posx = 0, posy = 0;
	int TargetPosx = 0, TargetPosy = 0;
	bool Active = false;
	int Cell[40][40];
	int AStarCell[40][40];
	int AStarDir[40][40];
	int x = 40, y = 40;
	int HP = 0, MinDMG = 0, MaxDMG = 0, ShieldDMG = 0, MaxHP = 0, Shield = 0, MagicShield = 0, View = 0;
	int Effect[10];
	int EffectTime[10];
	int Effect_size = 10;

	double distance(int x1, int y1, int x2, int y2)
	{
		int a = pow(x1 - x2, 2);
		int b = pow(y1 - y2, 2);
		int c = a + b;
		c = sqrt(c);
		return c;
	}
	void SetTarget(int x, int y) {
		TargetPosx = x;
		TargetPosy = y;
	}
	void Activate(int TargetPosX,int TargetPosY,int Cellx, int Celly, int hp, int maxhp, int shield, int mindmg, int maxdmg, int shielddmg) {
		for (int i = 0; i < Effect_size; i++) {
			Effect[i] = 0;
			EffectTime[i] = 0;
		}
		TargetPosx = TargetPosX;
		TargetPosy = TargetPosY;
		x = Cellx;
		y = Celly;
		Active = true;
		MaxHP = maxhp;
		Shield = shield;
		MinDMG = mindmg;
		MaxDMG = maxdmg;
		ShieldDMG = shielddmg;
		HP = hp;
		SetRandomTargetPos();
	}
	void SetHP(int hp) {
		HP = hp;
	}
	void SetRandomPos() {
		bool c = true;
		while (c == true) {
			int x1 = 0, y1 = 0;
			x1 = rand() % x;
			y1 = rand() % y;
			if (Cell[x1][y1] == 2) {
				c = false;
				posx = x1;
				posy = y1;
			}
		}
	}
	void SetRandomTargetPos() {
		bool c = true;
		while (c == true) {
			int x1 = 0, y1 = 0;
			x1 = rand() % x;
			y1 = rand() % y;
			if (Cell[x1][y1] == 2) {
				c = false;
				TargetPosx = x1;
				TargetPosy = y1;
			}
		}
	}
};