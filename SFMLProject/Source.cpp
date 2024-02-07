#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream> 
#include <Windows.h>
#include <math.h>
#include "Person.cpp"
#include "Player.cpp"
#include "Effect.h"
#pragma

using namespace sf;
using namespace std;

double distance(int x1, int y1, int x2, int y2)
{
	int a = pow(x1 - x2, 2);
	int b = pow(y1 - y2, 2);
	int c = a + b;
	c = sqrt(c);
	return c;
}

RectangleShape AddPixel(Vector2f position, Uint8 Red, Uint8 Green, Uint8 Blue, float XSize, float YSize) {
	RectangleShape pixel;
	pixel.setSize({ XSize, YSize });
	pixel.setFillColor({ Red, Green, Blue });
	pixel.setPosition(position);
	return pixel;
}

Font font;

Text Drawtext(Vector2f position, String str, int Size, Uint8 Red, Uint8 Green, Uint8 Blue) {
	Text text;
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(Size);
	text.setFillColor({ Red, Green, Blue });
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(position);
	return text;
}

int Cell[40][40];
int ViewCell[40][40];
int AStarCell[40][40];
int AStarDir[40][40];
int Pers[40][40];
int x = 40, y = 40, Q = 0, S1 = 5, S2 = 10, Stop = 0, Bx, By, Number = 0, Floor = 1;
Person Persons[5];
int Persons_size = 5;
Player PL;
Chest Chests[5];
int Chests_size = 5;
bool Press = true;

void DeleteSmall(int min) {
	int Cell2[40][40];
	int w = 0;
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			Cell2[i][ii] = Cell[i][ii];
		}
	}

	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell2[i][ii] == 2) {
				Cell2[i][ii] = 10;
				for (int q = 0; q < 100; q++) {
					for (int iii = 0; iii < x; iii++) {
						for (int iiii = 0; iiii < y; iiii++) {
							if (Cell2[iii][iiii] == 10) {
								if (Cell2[iii + 1][iiii] == 2) {
									Cell2[iii + 1][iiii] = 10;
								}
								if (Cell2[iii - 1][iiii] == 2) {
									Cell2[iii - 1][iiii] = 10;
								}
								if (Cell2[iii][iiii + 1] == 2) {
									Cell2[iii][iiii + 1] = 10;
								}
								if (Cell2[iii][iiii - 1] == 2) {
									Cell2[iii][iiii - 1] = 10;
								}
							}
						}
					}
				}

				for (int iii = 0; iii < x; iii++) {
					for (int iiii = 0; iiii < y; iiii++) {
						if (Cell2[iii][iiii] == 10) {
							w += 1;
						}
					}
				}
				if (w < min) {
					for (int iii = 0; iii < x; iii++) {
						for (int iiii = 0; iiii < y; iiii++) {
							if (Cell2[iii][iiii] == 10) {
								Cell2[iii][iiii] = 0;
							}
						}
					}
				}
				else {
					for (int iii = 0; iii < x; iii++) {
						for (int iiii = 0; iiii < y; iiii++) {
							if (Cell2[iii][iiii] == 10) {
								Cell2[iii][iiii] = 2;
							}
						}
					}
				}
				w = 0;
			}
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			Cell[i][ii] = Cell2[i][ii];
		}
	}
	cout << "!!! ";
}

void AStar(int x1, int y1, int x2, int y2, int num) {
	float MinDist = 999;
	int Mx = 0, My = 0;
	int CellA[40][40];
	int S = 0;

	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			CellA[i][ii] = Cell[i][ii];
		}
	}

	for (int i = 0; i < Persons_size; i++) {
		CellA[Persons[i].posx][Persons[i].posy] = 1;
	}

	CellA[x1][y1] = 2;

	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			AStarDir[i][ii] = 0;
			AStarCell[i][ii] = 0;
		}
	}

	AStarCell[x1][y1] = 2;
	if (CellA[x1 - 1][y1] == num) {
		AStarCell[x1 - 1][y1] = 1;
	}
	if (CellA[x1 + 1][y1] == num) {
		AStarCell[x1 + 1][y1] = 1;
	}
	if (CellA[x1][y1 - 1] == num) {
		AStarCell[x1][y1 - 1] = 1;
	}
	if (CellA[x1][y1 + 1] == num) {
		AStarCell[x1][y1 + 1] = 1;
	}

	AStarDir[x1 - 1][y1] = 1;
	AStarDir[x1 + 1][y1] = 2;
	AStarDir[x1][y1 - 1] = 3;
	AStarDir[x1][y1 + 1] = 4;

	while (AStarCell[x2][y2] != 2)
	{
		//cout << S << ' ';
		S++;
		if (S > 300) {
			goto A;
		}
		MinDist = 999;
		for (int i = 0; i < x; i++) {
			for (int ii = 0; ii < y; ii++) {
				if (AStarCell[i][ii] == 1 && distance(ii, i, y2, x2) < MinDist) {
					Mx = ii;
					My = i;
					MinDist = distance(ii, i, y2, x2);
				}
			}
		}

		AStarCell[My][Mx] = 2;
		if (CellA[My - 1][Mx] == num && AStarCell[My - 1][Mx] == 0) {
			AStarCell[My - 1][Mx] = 1;
			if (AStarDir[My - 1][Mx] == 0) {
				AStarDir[My - 1][Mx] = 1;
			}
		}
		if (CellA[My + 1][Mx] == num && AStarCell[My + 1][Mx] == 0) {
			AStarCell[My + 1][Mx] = 1;
			if (AStarDir[My + 1][Mx] == 0) {
				AStarDir[My + 1][Mx] = 2;
			}
		}
		if (CellA[My][Mx - 1] == num && AStarCell[My][Mx - 1] == 0) {
			AStarCell[My][Mx - 1] = 1;
			if (AStarDir[My][Mx - 1] == 0) {
				AStarDir[My][Mx - 1] = 3;
			}
		}
		if (CellA[My][Mx + 1] == num && AStarCell[My][Mx + 1] == 0) {
			AStarCell[My][Mx + 1] = 1;
			if (AStarDir[My][Mx + 1] == 0) {
				AStarDir[My][Mx + 1] = 4;
			}
		}
	}

A:

	int Nx = x2, Ny = y2;
	for (int i = 0; i < 100; i++) {
		if (AStarDir[Nx][Ny] == 1) {
			AStarCell[Nx][Ny] = 10;
			Nx += 1;
		}
		if (AStarDir[Nx][Ny] == 2) {
			AStarCell[Nx][Ny] = 10;
			Nx -= 1;
		}
		if (AStarDir[Nx][Ny] == 3) {
			AStarCell[Nx][Ny] = 10;
			Ny += 1;
		}
		if (AStarDir[Nx][Ny] == 4) {
			AStarCell[Nx][Ny] = 10;
			Ny -= 1;
		}
	}
}
void Generator(int maxh, int minh, int maxw, int minw) {
	bool run = true;
	bool run2 = true;
	int Cell2[40][40];
	int q = 0;
	while (run == true && q < 400) {
		run2 = true;
		q++;
		int x1 = 0, y1 = 0;
		x1 = rand() % (x - 10);
		y1 = rand() % (y - 10);
		int h = 0, w = 0;
		h = rand() % (maxh)+minh;
		w = rand() % (maxw)+minw;
		for (int i = 0; i < x; i++) {
			for (int ii = 0; ii < y; ii++) {
				if (i >= x1 && ii >= y1 && i <= x1 + w && ii <= y1 + h && Cell[i][ii] == 1) {
					run2 = false;
				}
				if (i >= x1 && ii >= y1 && i <= x1 + w && ii <= y1 + h && Cell[i][ii] == 2) {
					run2 = false;
				}
			}
		}
		if (run2 == true) {
			for (int i = 0; i < x; i++) {
				for (int ii = 0; ii < y; ii++) {
					if (i >= x1 && ii >= y1 && i <= x1 + w && ii <= y1 + h) {
						Cell[i][ii] = 1;
					}
				}
			}
			run = false;
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			Cell2[i][ii] = Cell[i][ii];
		}
	}

	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell2[i][ii] == 1 && Cell2[i + 1][ii] == 1 && Cell2[i - 1][ii] == 1 && Cell2[i][ii + 1] == 1 && Cell2[i][ii - 1] == 1 && Cell2[i + 1][ii + 1] == 1 && Cell2[i - 1][ii - 1] == 1 && Cell2[i - 1][ii + 1] == 1 && Cell2[i + 1][ii - 1] == 1) {
				Cell[i][ii] = 2;
			}
		}
	}

}

void PersonStep() {
	for (int i = 0; i < Persons_size; i++) {
		if (Persons[i].TargetPosx == Persons[i].posx && Persons[i].TargetPosy == Persons[i].posy) {
			bool q = true;
			while (q == true) {
				Persons[i].SetRandomTargetPos();
				for (int ii = 0; ii < Persons_size; ii++) {
					if (Persons[i].TargetPosx == Persons[ii].posx && Persons[i].TargetPosy == Persons[ii].posy) {
						q = true;
					}
					else {
						q = false;
					}
				}
			}
		}
		if (Persons[i].TargetPosx == PL.Posx && Persons[i].TargetPosy == PL.Posy && distance(Persons[i].posx, Persons[i].posy, Persons[i].TargetPosx, Persons[i].TargetPosy) > 3) {
			bool q = true;
			while (q == true) {
				Persons[i].SetRandomTargetPos();
				for (int ii = 0; ii < Persons_size; ii++) {
					if (Persons[i].TargetPosx == Persons[ii].posx && Persons[i].TargetPosy == Persons[ii].posy) {
						q = true;
					}
					else {
						q = false;
					}
				}
			}
		}
		if (distance(Persons[i].posx, Persons[i].posy, PL.Posx, PL.Posy) < 3) {
			Persons[i].SetTarget(PL.Posx, PL.Posy);
		}
		AStar(Persons[i].posx, Persons[i].posy, Persons[i].TargetPosx, Persons[i].TargetPosy, 2);
		if (AStarCell[Persons[i].posx + 1][Persons[i].posy] == 10 && Vector2f(Persons[i].posx + 1, Persons[i].posy) != Vector2f(PL.Posx, PL.Posy)) {
			Persons[i].posx += 1;
			AStarCell[Persons[i].posx + 1][Persons[i].posy] = 0;
		}
		if (AStarCell[Persons[i].posx - 1][Persons[i].posy] == 10 && Vector2f(Persons[i].posx - 1, Persons[i].posy) != Vector2f(PL.Posx, PL.Posy)) {
			Persons[i].posx -= 1;
			AStarCell[Persons[i].posx - 1][Persons[i].posy] = 0;
		}
		if (AStarCell[Persons[i].posx][Persons[i].posy + 1] == 10 && Vector2f(Persons[i].posx, Persons[i].posy + 1) != Vector2f(PL.Posx, PL.Posy)) {
			Persons[i].posy += 1;
			AStarCell[Persons[i].posx][Persons[i].posy + 1] = 0;
		}
		if (AStarCell[Persons[i].posx][Persons[i].posy - 1] == 10 && Vector2f(Persons[i].posx, Persons[i].posy - 1) != Vector2f(PL.Posx, PL.Posy)) {
			Persons[i].posy -= 1;
			AStarCell[Persons[i].posx][Persons[i].posy - 1] = 0;
		}
		if (Persons[i].Active == true) {
			int dmg = (PL.Shield - Persons[i].ShieldDMG) - Persons[i].MinDMG - rand() % (Persons[i].MaxDMG - Persons[i].MinDMG + 1);
			if (Persons[i].posx == PL.Posx - 1 && Persons[i].posy == PL.Posy) {
				if (dmg < 0) {
					PL.HP += dmg;
				}
				cout << "Person DMG: " << dmg << "\n";
			}
			if (Persons[i].posx == PL.Posx + 1 && Persons[i].posy == PL.Posy) {
				if (dmg < 0) {
					PL.HP += dmg;
				}
				cout << "Person DMG: " << dmg << "\n";
			}
			if (Persons[i].posx == PL.Posx && Persons[i].posy == PL.Posy - 1) {
				if (dmg < 0) {
					PL.HP += dmg;
				}
				cout << "Person DMG: " << dmg << "\n";
			}
			if (Persons[i].posx == PL.Posx && Persons[i].posy == PL.Posy + 1) {
				if (dmg < 0) {
					PL.HP += dmg;
				}
				cout << "Person DMG: " << dmg << "\n";
			}
		}
		for (int ii = 0; ii < Persons[i].Effect_size; ii++) {
			switch (Persons[i].Effect[ii])
			{
			case 1: {
				Persons[i].HP -= Bleeding(2, Persons[i].MaxHP);
				cout << Bleeding(2, Persons[i].MaxHP) << '!';
				break;
			}
			default: {
				break;
			}
			}
		}

	}
	//Sleep(100);
}

void NewFloor() {
Q:
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			Cell[i][ii] = 0;
			ViewCell[i][ii] = 0;
		}
	}

	for (int i = 0; i < 3; i++) {
		Generator(14, 8, 14, 8);
	}
	for (int i = 0; i < 20; i++) {
		Generator(8, 4, 8, 4);
	}
	for (int i = 0; i < 20; i++) {
		Generator(6, 3, 6, 3);
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 2 && Cell[i - 1][ii] == 2 && Cell[i][ii + 1] == 1 && Cell[i][ii - 1] == 1) {
				Cell[i][ii] = 2;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 2 && Cell[i][ii - 1] == 2 && Cell[i + 1][ii] == 1 && Cell[i - 1][ii] == 1) {
				Cell[i][ii] = 2;
			}
		}
	}
	DeleteSmall(400);

	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < y; i++) {
		if (Cell[i][0] == 2) {
			Cell[i][0] = 1;
		}
		if (Cell[i][x - 1] == 2) {
			Cell[i][x - 1] = 1;
		}
		if (Cell[0][i] == 2) {
			Cell[0][i] = 1;
		}
		if (Cell[x - 1][i] == 2) {
			Cell[x - 1][i] = 1;
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 2) {
				Number++;
			}
		}
	}
	if (Number < 10) {
		Number = 0;
		goto Q;
	}
	Number = 0;
	DeleteSmall(400);
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 2) {
				Number++;
			}
		}
	}
	if (Number < 10) {
		Number = 0;
		goto Q;
	}
	Number = 0;
	Sleep(100);
	for (int i = 0; i < Persons_size; i++) {
		for (int ii = 0; ii < x; ii++) {
			for (int iii = 0; iii < y; iii++) {
				Persons[i].Cell[ii][iii] = Cell[ii][iii];
			}
		}
		Persons[i].SetRandomPos();
		Persons[i].Activate(PL.Posx, PL.Posy, x, y, 10, 10, 2, 6, 12, 1);
	}

	for (int i = x; i > 1; i--) {
		for (int ii = y; ii > 1; ii--) {
			if (Cell[ii][i] == 2) {
				PL.Posx = ii;
				PL.Posy = i;
			}
		}
	}

	bool c = true;
	while (c == true) {
		int x1 = 0, y1 = 0;
		x1 = rand() % x;
		y1 = rand() % y;
		if (Cell[x1][y1] == 2) {
			c = false;
			Bx = x1;
			By = y1;
		}
	}

	for (int i = 0; i < Chests_size; i++) {
		bool c = true;
		while (c == true) {
			int x1 = 0, y1 = 0;
			x1 = rand() % x;
			y1 = rand() % y;
			if (Cell[x1][y1] == 2 && x1 != Bx && y1 != By) {
				c = false;
				Chests[i].Posx = x1;
				Chests[i].Posy = y1;
				Chests[i].Activate(Floor, rand() % 1000000000000);
			}
		}
	}
}

int main()
{
	font.loadFromFile("1.ttf");

	srand(time(0));

	RenderWindow window(VideoMode(800, 600), "SFMLworks");

	float Step = 0;

	//PL.Bag[0].ItemFunction(2);
	//PL.Bag[1].ItemFunction(3);
	//PL.Bag[2].ItemFunction(4);
	//PL.Bag[3].ItemFunction(6);
	//PL.Bag[4].ItemFunction(7);
	//PL.Bag[5].ItemFunction(5);

	PL.Weapon.ItemFunction(1);

Q:
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			Cell[i][ii] = 0;
		}
	}

	for (int i = 0; i < 3; i++) {
		Generator(14, 8, 14, 8);
	}
	for (int i = 0; i < 20; i++) {
		Generator(8, 4, 8, 4);
	}
	for (int i = 0; i < 20; i++) {
		Generator(6, 3, 6, 3);
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 2 && Cell[i - 1][ii] == 2 && Cell[i][ii + 1] == 1 && Cell[i][ii - 1] == 1) {
				Cell[i][ii] = 2;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 2 && Cell[i][ii - 1] == 2 && Cell[i + 1][ii] == 1 && Cell[i - 1][ii] == 1) {
				Cell[i][ii] = 2;
			}
		}
	}
	DeleteSmall(400);

	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < y; i++) {
		if (Cell[i][0] == 2) {
			Cell[i][0] = 1;
		}
		if (Cell[i][x - 1] == 2) {
			Cell[i][x - 1] = 1;
		}
		if (Cell[0][i] == 2) {
			Cell[0][i] = 1;
		}
		if (Cell[x - 1][i] == 2) {
			Cell[x - 1][i] = 1;
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 2) {
				Number++;
			}
		}
	}
	if (Number < 10) {
		Number = 0;
		goto Q;
	}
	Number = 0;
	DeleteSmall(400);
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 1 && Cell[i + 1][ii] == 0 && Cell[i - 1][ii] == 0) {
				Cell[i][ii] = 0;
			}
			if (Cell[i][ii] == 1 && Cell[i][ii + 1] == 0 && Cell[i][ii - 1] == 0) {
				Cell[i][ii] = 0;
			}
		}
	}
	for (int i = 0; i < x; i++) {
		for (int ii = 0; ii < y; ii++) {
			if (Cell[i][ii] == 2) {
				Number++;
			}
		}
	}
	if (Number < 10) {
		Number = 0;
		goto Q;
	}
	Number = 0;
	Sleep(100);
	for (int i = 0; i < Persons_size; i++) {
		for (int ii = 0; ii < x; ii++) {
			for (int iii = 0; iii < y; iii++) {
				Persons[i].Cell[ii][iii] = Cell[ii][iii];
			}
		}
		Persons[i].SetRandomPos();
		Persons[i].Activate(PL.Posx, PL.Posy, x, y, 10, 10, 2, 6, 12, 1);
	}

	for (int i = x; i > 1; i--) {
		for (int ii = y; ii > 1; ii--) {
			if (Cell[ii][i] == 2) {
				PL.Posx = ii;
				PL.Posy = i;
			}
		}
	}

	bool c = true;
	while (c == true) {
		int x1 = 0, y1 = 0;
		x1 = rand() % x;
		y1 = rand() % y;
		if (Cell[x1][y1] == 2) {
			c = false;
			Bx = x1;
			By = y1;
		}
	}

	for (int i = 0; i < Chests_size; i++) {
		bool c = true;
		while (c == true) {
			int x1 = 0, y1 = 0;
			x1 = rand() % x;
			y1 = rand() % y;
			if (Cell[x1][y1] == 2 && x1 != Bx && y1 != By) {
				c = false;
				Chests[i].Posx = x1;
				Chests[i].Posy = y1;
				Chests[i].Activate(Floor, rand() % 1000000000000);
				cout << Chests[i].IteamInChest.name << "\n";
			}
		}
	}

	while (window.isOpen())
	{
		window.clear();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		/*
		for (int i = 0; i < x; i++) {
			for (int ii = 0; ii < y; ii++) {
				if (Cell[i][ii] == 0) {
					window.draw(AddPixel({ (float)i * S2,(float)ii * S2 }, 0, 0, 0, S2, S2));
				}
				else if (Cell[i][ii] == 1) {
					window.draw(AddPixel({ (float)i * S2,(float)ii * S2 }, 255, 255, 255, S2, S2));
				}
				else if (Cell[i][ii] == 2 && distance(i, ii, PL.Posx, PL.Posy) > 5) {
					window.draw(AddPixel({ (float)i * S2,(float)ii * S2 }, 55, 55, 55, S2, S2));
				}
				else if (Cell[i][ii] == 2) {
					window.draw(AddPixel({ (float)i * S2,(float)ii * S2 }, 100, 100, 100, S2, S2));
				}
			}
		}
		*/

		for (int i = 0; i < x; i++) {
			for (int ii = 0; ii < y; ii++) {
				if (ViewCell[i][ii] == 1) {
					window.draw(AddPixel({ (float)i * S2,(float)ii * S2 }, 180, 180, 180, S2, S2));
				}
				else if (ViewCell[i][ii] == 2) {
					window.draw(AddPixel({ (float)i * S2,(float)ii * S2 }, 50, 50, 50, S2, S2));
				}
			}
		}

		for (int i = 0; i < x; i++) {
			for (int ii = 0; ii < y; ii++) {
				Pers[i][ii] = 0;
			}
		}

		for (int i = 0; i < 360; i += 1) {
			for (int ii = 0; ii < 500; ii += 5) {
				int x = ii * sin(i), y = ii * cos(i);
				if (Cell[x / S2 + PL.Posx][y / S2 + PL.Posy] == 1) {
					window.draw(AddPixel({ (float)(x / S2 + PL.Posx) * S2,(float)(y / S2 + PL.Posy) * S2 }, 255, 255, 255, S2, S2));
					ViewCell[x / S2 + PL.Posx][y / S2 + PL.Posy] = Cell[x / S2 + PL.Posx][y / S2 + PL.Posy];
					goto M;
				}
				else if (Cell[x / S2 + PL.Posx][y / S2 + PL.Posy] == 2) {
					window.draw(AddPixel({ (float)(x / S2 + PL.Posx) * S2,(float)(y / S2 + PL.Posy) * S2 }, 80, 80, 80, S2, S2));
					ViewCell[x / S2 + PL.Posx][y / S2 + PL.Posy] = Cell[x / S2 + PL.Posx][y / S2 + PL.Posy];
				}
				for (int i = 0; i < Chests_size; i++) {
					if (Chests[i].Posx == x / S2 + PL.Posx && Chests[i].Posy == y / S2 + PL.Posy) {
						window.draw(AddPixel({ (float)Chests[i].Posx * S2,(float)Chests[i].Posy * S2 }, 255, 255, 0, S2, S2));
					}
				}
				for (int i = 0; i < Persons_size; i++) {
					if (Persons[i].posx == x / S2 + PL.Posx && Persons[i].posy == y / S2 + PL.Posy && Persons[i].Active == true) {
						window.draw(AddPixel({ (float)Persons[i].posx * S2,(float)Persons[i].posy * S2 - 3 }, 0, 255, 0, ((float)S2 / Persons[i].MaxHP) * Persons[i].HP, S2));
						window.draw(AddPixel({ (float)Persons[i].posx * S2,(float)Persons[i].posy * S2 }, 255, 0, 0, S2, S2));
						goto M;
					}
				}
				if (Bx == x / S2 + PL.Posx && By == y / S2 + PL.Posy) {
					window.draw(AddPixel({ (float)Bx * S2,(float)By * S2 }, 0, 255, 0, S2, S2));
				}
			}
		M:
			cout << "";
		}
		window.draw(AddPixel({ (float)PL.Posx * S2,(float)PL.Posy * S2 }, 0, 255, 255, S2, S2));

		for (int i = 0; i < Persons_size; i++) {
			if (Persons[i].View > 0) {
				window.draw(AddPixel({ (float)Persons[i].posx * S2,(float)Persons[i].posy * S2 - 3 }, 0, 255, 0, ((float)S2 / Persons[i].MaxHP) * Persons[i].HP, S2));
				window.draw(AddPixel({ (float)Persons[i].posx * S2,(float)Persons[i].posy * S2 }, 255, 0, 0, S2, S2));
			}
		}

		//cout << Bx << ' ' << By << ' ' << distance(Bx, By, PL.Posx, PL.Posy) <<"\n";

		window.draw(Drawtext({ (float)500,(float)20 }, "HP: " + to_string(PL.HP), 20, 255, 0, 0));
		window.draw(Drawtext({ (float)600,(float)20 }, "Step: " + to_string(round(Step * 100) / 100), 20, 255, 255, 255));

		window.draw(Drawtext({ (float)500,(float)50 }, "Bag: ", 20, 255, 255, 255));

		for (int i = 0; i < PL.BagSize; i++) {
			if (i == PL.BagSelected) {
				window.draw(Drawtext({ (float)490,(float)i * 20 + 80 }, "[", 20, 255, 255, 0));
			}
			if (PL.Bag[i].Rarity == 0) {
				window.draw(Drawtext({ (float)500,(float)i * 20 + 80 }, to_string(i) + ": " + PL.Bag[i].name, 20, 255, 255, 255));
			}
			else if (PL.Bag[i].Rarity == 1) {
				window.draw(Drawtext({ (float)500,(float)i * 20 + 80 }, to_string(i) + ": " + PL.Bag[i].name, 20, 0, 255, 0));
			}
			else if (PL.Bag[i].Rarity == 2) {
				window.draw(Drawtext({ (float)500,(float)i * 20 + 80 }, to_string(i) + ": " + PL.Bag[i].name, 20, 0, 255, 255));
			}
			else if (PL.Bag[i].Rarity == 3) {
				window.draw(Drawtext({ (float)500,(float)i * 20 + 80 }, to_string(i) + ": " + PL.Bag[i].name, 20, 255, 100, 255));
			}
			else if (PL.Bag[i].Rarity == 4) {
				window.draw(Drawtext({ (float)500,(float)i * 20 + 80 }, to_string(i) + ": " + PL.Bag[i].name, 20, 255, 255, 0));
			}
		}

		if (PL.Weapon.Rarity == 0) {
			window.draw(Drawtext({ (float)500,(float)220 }, "Weapon: " + PL.Weapon.name, 20, 255, 255, 255));
		}
		else if (PL.Weapon.Rarity == 1) {
			window.draw(Drawtext({ (float)500,(float)220 }, "Weapon: " + PL.Weapon.name, 20, 0, 255, 0));
		}
		else if (PL.Weapon.Rarity == 2) {
			window.draw(Drawtext({ (float)500,(float)220 }, "Weapon: " + PL.Weapon.name, 20, 0, 255, 255));
		}
		else if (PL.Weapon.Rarity == 3) {
			window.draw(Drawtext({ (float)500,(float)220 }, "Weapon: " + PL.Weapon.name, 20, 255, 100, 255));
		}
		else if (PL.Weapon.Rarity == 4) {
			window.draw(Drawtext({ (float)500,(float)220 }, "Weapon: " + PL.Weapon.name, 20, 255, 255, 0));
		}

		for (int i = 0; i < Chests_size; i++) {
			if (Chests[i].Posx == PL.Posx && Chests[i].Posy == PL.Posy) {
				if (Chests[i].IteamInChest.Rarity == 0) {
					window.draw(Drawtext({ (float)500,(float)250 }, "Chests: " + Chests[i].IteamInChest.name, 20, 255, 255, 255));
				}
				else if (Chests[i].IteamInChest.Rarity == 1) {
					window.draw(Drawtext({ (float)500,(float)250 }, "Chests: " + Chests[i].IteamInChest.name, 20, 0, 255, 0));
				}
				else if (Chests[i].IteamInChest.Rarity == 2) {
					window.draw(Drawtext({ (float)500,(float)250 }, "Chests: " + Chests[i].IteamInChest.name, 20, 0, 255, 255));
				}
				else if (Chests[i].IteamInChest.Rarity == 3) {
					window.draw(Drawtext({ (float)500,(float)250 }, "Chests: " + Chests[i].IteamInChest.name, 20, 255, 100, 255));
				}
				else if (Chests[i].IteamInChest.Rarity == 4) {
					window.draw(Drawtext({ (float)500,(float)250 }, "Chests: " + Chests[i].IteamInChest.name, 20, 255, 255, 0));
				}
			}
		}

		window.draw(Drawtext({ (float)20,(float)450 }, "description: " + PL.Bag[PL.BagSelected].description + PL.Bag[PL.BagSelected].PropertiesDescription, 15, 255, 255, 255));

		if (Keyboard::isKeyPressed(Keyboard::Q)) {
			for (int i = 0; i < Chests_size; i++) {
				if (Chests[i].Posx == PL.Posx && Chests[i].Posy == PL.Posy) {
					Item item;
					item = PL.Bag[PL.BagSelected];
					PL.Bag[PL.BagSelected] = Chests[i].IteamInChest;
					Chests[i].IteamInChest = item;
				}
			}
			Sleep(20);
		}

		if (Keyboard::isKeyPressed(Keyboard::E) && PL.Posx == Bx && PL.Posy == By) {
			NewFloor();
		}
		if (Keyboard::isKeyPressed(Keyboard::R)) {
			PersonStep();
			Sleep(90);
		}
		if (Keyboard::isKeyPressed(Keyboard::X)) {
			PL.BagSelected += 1;
			if (PL.BagSelected >= PL.BagSize) {
				PL.BagSelected = 0;
			}
			Sleep(90);
		}
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			if (PL.Bag[PL.BagSelected].tag == "weapon") {
				Item item;
				item = PL.Weapon;
				PL.Weapon = PL.Bag[PL.BagSelected];
				PL.Bag[PL.BagSelected] = item;
			}
			if (PL.Bag[PL.BagSelected].tag == "plpotion") {
				PL.Potion(PL.Bag[PL.BagSelected].Effect);
				cout << PL.Bag[PL.BagSelected].Effect;
				if (PL.Bag[PL.BagSelected].Effect == 2) {
					for (int i = 0; i < x; i++) {
						for (int ii = 0; ii < y; ii++) {
							ViewCell[i][ii] = Cell[i][ii];
						}
					}
				}
				if (PL.Bag[PL.BagSelected].Effect == 3) {
					for (int i = 0; i < Persons_size; i++) {
						Persons[i].View = 20;
					}
				}
				PL.Bag[PL.BagSelected].ItemFunction(0);
			}
			Sleep(90);
		}
		/*
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			AStar(Px, Py, Bx, By, 2);
			Sleep(100);
		}
		*/
		if (Keyboard::isKeyPressed(Keyboard::Right) && Cell[PL.Posx + 1][PL.Posy] == 2)
		{
			PL.Posx += 1;
			Sleep(90);
			Step++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && Cell[PL.Posx - 1][PL.Posy] == 2)
		{
			PL.Posx -= 1;
			Sleep(90);
			Step++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && Cell[PL.Posx][PL.Posy + 1] == 2)
		{
			PL.Posy += 1;
			Sleep(90);
			Step++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && Cell[PL.Posx][PL.Posy - 1] == 2)
		{
			PL.Posy -= 1;
			Sleep(90);
			Step++;
		}
		/*
		if (Step < 1) {
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				for (int i = 0; i < Persons_size; i++) {
					if (Persons[i].posx == PL.Posx && Persons[i].posy == PL.Posy - 1) {
						int dmg = (Persons[i].Shield - PL.Weapon.ShieldDMG) - PL.Weapon.MinDMG + rand() % (PL.Weapon.MaxDMG - PL.Weapon.MinDMG + 1);
						if (dmg < 0) {
							Persons[i].HP += dmg;
						}
						cout << "PL DMG:" << dmg << "\n";
					}
				}
				Sleep(90);
				Step += PL.Weapon.AttackSpeed;
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				for (int i = 0; i < Persons_size; i++) {
					if (Persons[i].posx == PL.Posx - 1 && Persons[i].posy == PL.Posy) {
						int dmg = (Persons[i].Shield - PL.Weapon.ShieldDMG) - PL.Weapon.MinDMG + rand() % (PL.Weapon.MaxDMG - PL.Weapon.MinDMG + 1);
						if (dmg < 0) {
							Persons[i].HP += dmg;
						}
						cout << "PL DMG:" << dmg << "\n";
					}
				}
				Sleep(90);
				Step += PL.Weapon.AttackSpeed;
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				for (int i = 0; i < Persons_size; i++) {
					if (Persons[i].posx == PL.Posx && Persons[i].posy == PL.Posy + 1) {
						int dmg = (Persons[i].Shield - PL.Weapon.ShieldDMG) - PL.Weapon.MinDMG + rand() % (PL.Weapon.MaxDMG - PL.Weapon.MinDMG + 1);
						if (dmg < 0) {
							Persons[i].HP += dmg;
						}
						cout << "PL DMG:" << dmg << "\n";
					}
				}
				Sleep(90);
				Step += PL.Weapon.AttackSpeed;
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				for (int i = 0; i < Persons_size; i++) {
					if (Persons[i].posx == PL.Posx + 1 && Persons[i].posy == PL.Posy) {
						int dmg = (Persons[i].Shield - PL.Weapon.ShieldDMG) - PL.Weapon.MinDMG + rand() % (PL.Weapon.MaxDMG - PL.Weapon.MinDMG + 1);
						if (dmg < 0) {
							Persons[i].HP += dmg;
						}
						cout << "PL DMG:" << dmg << "\n";
					}
				}
				Sleep(90);
				Step += PL.Weapon.AttackSpeed;
			}
		}
		*/
		//cout << Step << "!!" << "\n";
		if (Step >= 1) {
			PersonStep();
			Step -= 1;
			for (int i = 0; i < Persons_size; i++) {
				Persons[i].View--;
			}
			//Sleep(30);
		}
		if (Step < 0) {
			Step = 0;
		}

		if (event.type == event.MouseButtonPressed && event.mouseButton.button == Mouse::Left && Press == true)
		{
			Press = false;
			int x1 = (PL.Posx * S2) + S2 / 2, y1 = (PL.Posy * S2) + S2 / 2, x2 = Mouse::getPosition(window).x, y2 = Mouse::getPosition(window).y;
			int dx = (x2 - x1 >= 0 ? 1 : -1);
			int dy = (y2 - y1 >= 0 ? 1 : -1);
			int lengthX = abs(x2 - x1);
			int lengthY = abs(y2 - y1);
			int length = max(lengthX, lengthY);
			Step += PL.Weapon.AttackSpeed;
			for (int i = 0; i < x; i++) {
				for (int ii = 0; ii < y; ii++) {
					Pers[i][ii] = 0;
				}
			}
			for (int i = 0; i < Persons_size; i++) {
				if (Persons[i].Active == true) {
					Pers[Persons[i].posx][Persons[i].posy] = 1;
				}
			}

			if (length == 0) {
				window.draw(AddPixel({ (float)x1,(float)y1 }, 0, 255, 0, 1, 1));
			}
			if (lengthY <= lengthX) {
				int x = x1;
				int y = y1;
				int d = -lengthX;
				length++;
				while (length--)
				{
					if (Cell[x / S2][y / S2] == 1) {
						goto D;
					}
					if (Pers[x / S2][y / S2] == 1) {
						for (int iii = 0; iii < Persons_size; iii++) {
							if (Persons[iii].Active == true && Persons[iii].posx == x / S2 && Persons[iii].posy == y / S2) {
								Persons[iii].TargetPosx = PL.Posx;
								Persons[iii].TargetPosy = PL.Posy;
								int dmg = (Persons[iii].Shield - PL.Weapon.ShieldDMG) - PL.Weapon.MinDMG - rand() % (PL.Weapon.MaxDMG - PL.Weapon.MinDMG + 1);
								if (dmg < 0) {
									Persons[iii].HP += dmg;
								}
								for (int iiii = 0; iiii < Persons[iii].Effect_size; iiii++) {
									if (Persons[iii].Effect[iiii] == 0) {
										Persons[iii].Effect[iiii] = PL.Weapon.Effect;
										Persons[iii].EffectTime[iiii] = PL.Weapon.EffectTime;
										cout << Persons[iii].Effect[iiii] << '!';
										break;
									}
								}
								cout << "PL DMG:" << dmg << "\n";
								goto D;
							}
						}
						goto D;
					}
					if (distance(x / S2, y / S2, PL.Posx, PL.Posy) <= PL.Weapon.AttackDistance) {
						window.draw(AddPixel({ (float)x,(float)y }, 0, 255, 0, 1, 1));
					}
					else {
						goto D;
					}
					x += dx;
					d += 2 * lengthY;
					if (d > 0) {
						d -= 2 * lengthX;
						y += dy;
					}
				}
			}
			else
			{
				int x = x1;
				int y = y1;
				int d = -lengthY;
				length++;
				while (length--)
				{
					if (Cell[x / S2][y / S2] == 1) {
						goto D;
					}
					if (Pers[x / S2][y / S2] == 1) {
						for (int iii = 0; iii < Persons_size; iii++) {
							if (Persons[iii].Active == true && Persons[iii].posx == x / S2 && Persons[iii].posy == y / S2) {
								Persons[iii].TargetPosx = PL.Posx;
								Persons[iii].TargetPosy = PL.Posy;
								int dmg = (Persons[iii].Shield - PL.Weapon.ShieldDMG) - PL.Weapon.MinDMG - rand() % (PL.Weapon.MaxDMG - PL.Weapon.MinDMG + 1);
								if (dmg < 0) {
									Persons[iii].HP += dmg;
								}
								for (int iiii = 0; iiii < Persons[iii].Effect_size; iiii++) {
									if (Persons[iii].Effect[iiii] == 0) {
										Persons[iii].Effect[iiii] = PL.Weapon.Effect;
										Persons[iii].EffectTime[iiii] = PL.Weapon.EffectTime;
										cout << Persons[iii].Effect[iiii] << '!';
										break;
									}
								}
								cout << "PL DMG:" << dmg << "\n";
								goto D;
							}
						}
					}
					if (distance(x / S2, y / S2, PL.Posx, PL.Posy) <= PL.Weapon.AttackDistance) {
						window.draw(AddPixel({ (float)x,(float)y }, 0, 255, 0, 1, 1));
					}
					else {
						goto D;
					}
					y += dy;
					d += 2 * lengthX;
					if (d > 0) {
						d -= 2 * lengthY;
						x += dx;
					}
				}
			}
			//PL.Posx = Mouse::getPosition(window).x / S2;
			//PL.Posy = Mouse::getPosition(window).y / S2;
		}
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
			Press = true;
		}
	D:
		if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Right)
		{
			//Bx = Mouse::getPosition(window).x / S2;
			//By = Mouse::getPosition(window).y / S2;
		}

		for (int i = 0; i < Persons_size; i++) {
			if (Persons[i].HP <= 0) {
				Persons[i].Active = false;
			}
		}




		window.display();
	}
	return 0;
}

