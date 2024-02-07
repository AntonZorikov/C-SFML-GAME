#include "Effect.h"

int Bleeding(int lvl, int MaxHP) {
	int hp = (float) MaxHP / 100 * 5 * lvl;
	return hp;
}
