#include "state.h"

int BOX_SIZE;
int *box;

int* acs(int x, int y) {
	return &box[x*BOX_SIZE+y];
}
int view(int x, int y)
{
	return box[x*BOX_SIZE + y];
}

