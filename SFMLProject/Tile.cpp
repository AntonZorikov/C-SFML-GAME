#include <iostream>
#include <math.h>
#include <Windows.h>

class Tiles {
public:
	int T[40][40];
	int Th = 0, Tw = 0, Tm = 0;

	int T1[3][3] = { {3,4,3},
					 {1,2,1},
					 {3,4,3} };
	int T1h = 3, T1w = 3, T1m = 2;
	int T2[3][3] = { {3,1,3},
					 {4,2,4},
					 {3,1,3} };
	int T2h = 3, T2w = 3, T2m = 2;
	int T3[3][3] = { {1,1,3},
					 {1,2,4},
					 {3,4,3} };
	int T3h = 3, T3w = 3, T3m = 2;
	int T4[3][3] = { {3,1,1},
					 {4,2,1},
					 {3,4,3} };
	int T4h = 3, T4w = 3, T4m = 2;
	int T5[3][3] = { {3,4,3},
					 {4,2,1},
					 {3,1,1} };
	int T5h = 3, T5w = 3, T5m = 2;
	int T6[3][3] = { {3,4,3},
					 {1,2,4},
					 {1,1,3} };
	int T6h = 3, T6w = 3, T6m = 2;
	void TileFunction(int t) {
		switch (t)
		{
		case 0: {
			int Tf[3][3] = { {3,4,3},
					 {1,2,1},
					 {3,4,3} };
			Th = 3;
			Tw = 3;
			Tm = 2;
			for (int i = 0; i < 3; i++) {
				for (int ii = 0; ii < 3; ii++) {
					T[i][ii] = Tf[i][ii];
				}
			}
			break;
		}
		default: {
			break;
		}
		}
	}
};