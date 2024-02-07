#include <iostream>
#include <math.h>
#include <Windows.h>
#include "Item.cpp"

class Player {
public:
	int Posx = 0, Posy = 0;
	int HP = 100, MaxHP = 100, DMG = 0, Shield = 2;
	int BagSize = 6;
	int BagSelected = 0;
	Item Weapon;
	Item Bag[8];
	void Potion(int Effect) {
		switch (Effect)
		{
		case 1: {
			HP += 20;
			if (HP > MaxHP) {
				HP = MaxHP;
			}
			break;
		}
		default: {
			break;
		}
		}
	}
};

class Chest {
public:
	int Posx = 0, Posy = 0;
	Item IteamInChest;
	void Activate(int Floor, int t) {
		srand(t);
		if(rand() % 100 < 0){
			switch (Floor)
			{
			case 1: {
				int Items0[3] = { 2,3,7 };
				int Items1[1] = { 4 };
				int Items2[2] = { 5,6 };
				int Items3[1] = { 8 };
				int rnd = rand() % 100;
				if (rnd <= 70) {
					IteamInChest.ItemFunction(Items0[rand() % 3]);
				}
				else if (rnd <= 85 && rnd > 70) {
					IteamInChest.ItemFunction(Items1[0]);
				}
				else if (rnd <= 93 && rnd > 85) {
					IteamInChest.ItemFunction(Items2[rand() % 2]);
				}
				else if (rnd <= 97 && rnd > 93) {
					IteamInChest.ItemFunction(Items3[0]);
				}
				else {
					IteamInChest.ItemFunction(Items0[rand() % 3]);
				}
				break;
			}
			default: {
				break;
			}
			}
		}
		else {
			switch (Floor)
			{
			case 1: {
				int Items[3] = { -1, -2, -3 };
				IteamInChest.ItemFunction(Items[rand() % 3]);
				break;
			}
			default: {
				break;
			}
			}
		}
	}
};