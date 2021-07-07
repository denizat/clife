#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BOX_SIZE 25

int box[BOX_SIZE][BOX_SIZE];

void
clearBox()
{
	for(int i =0; i<BOX_SIZE;i++){
		for(int k=0;k<BOX_SIZE;k++) {
			box[i][k] = 0;
		}
	}
}

void
randBox()
{
	for(int i =0; i<BOX_SIZE;i++){
		for(int k=0;k<BOX_SIZE;k++) {
			if(rand()%10 > 7)
				box[i][k] = 1;
		}
	}
}

void
href()
{
	for(int i=0;i<BOX_SIZE;i++)
		printf("--");
	printf("\n");
}

void
showBox()
{
		printf("\n");
		printf("\n");
	for(int i =0; i<BOX_SIZE;i++){
		href();
		printf("|");
		for(int k=0;k<BOX_SIZE;k++) {
			if(box[i][k] == 1)
				printf("8|");
			else
				printf(" |");
		}
		printf("\n");
	}
		printf("\n");
		printf("\n");
}

int
fix(int n)
{
	if(n==-1)
		return BOX_SIZE-1;
	if(n==BOX_SIZE)
		return 0;
	return n;
}
int
fixed(int x, int y)
{
	return box[fix(x)][fix(y)];
}
// Counts number of alive neighbors of a cell
int
neighbors(int x, int y)
{
	int alive = 0;


	if(fixed(x-1,y-1)==1)
		alive++;
	if(fixed(x-1,y)==1)
		alive++;
	if(fixed(x-1,y+1)==1)
		alive++;
	if(fixed(x,y-1)==1)
		alive++;
	if(fixed(x,y+1)==1)
		alive++;
	if(fixed(x+1,y-1)==1)
		alive++;
	if(fixed(x+1,y)==1)
		alive++;
	if(fixed(x+1,y+1)==1)
		alive++;
	return alive;
}

void
iterate() {
	int n;
	for(int i = 0; i<BOX_SIZE;i++) {
		for(int k=0;k<BOX_SIZE;k++){
				n = neighbors(i,k);
			if(box[i][k]) {
				if(!(n==2 || n==3)) {
					box[i][k] = 0;
				}

			} else {
				if(n == 3)
					box[i][k] = 1;
			}
		}
	}
}



int
main(int argv, char **argc) {
	/* if(argv < 2) { */
	/* 	printf("Please give me a box size\n"); */
	/* 	return 1; */
	/* } */
	/* randBox(); */
	struct timespec tim;
	tim.tv_sec = 0;
	tim.tv_nsec = 50000000L;
	/* tim.tv_nsec = 100000000L; */
	randBox();
	for(;;nanosleep(&tim,NULL)) {
		showBox();
		iterate();
	}
	return 0;
}

