#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "view.h"
#include "state.h"




void
clearBox()
{
	for(int i =0; i<BOX_SIZE;i++){
		for(int k=0;k<BOX_SIZE;k++) {
			*acs(i,k) = 0;
		}
	}
}

void
randBox()
{
	for(int i =0; i<BOX_SIZE;i++){
		for(int k=0;k<BOX_SIZE;k++) {
			if(rand()%10 > 7)
				*acs(i,k) = 1;
		}
	}
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
	return view(fix(x),fix(y));
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
			if(view(i,k)) {
				if(!(n==2 || n==3)) {
					printf("Death at(%d,%d)\tNeighbors:(%d)\n",i,k,n);
					*acs(i,k) = 0;
				}

			} else {
				if(n == 3){
					printf("Life at(%d,%d)\tNeighbors:(%d)\n",i,k,n);
					*acs(i,k) = 1;
				}
			}
		}
	}
}



int
main(int argv, char **argc) {
	if(argv < 2) {
		printf("Please give me a box size\n");
		return 1;
	}
	BOX_SIZE = atoi(argc[1]);
	box = (int *)malloc(BOX_SIZE*BOX_SIZE*sizeof(int));
	/* randBox(); */
	struct timespec tim;
	tim.tv_sec = 0;
	/* tim.tv_nsec = 50000000L; */
	tim.tv_nsec = 100000000L;
	/* randBox(); */
	*acs(0,0)=1;
	*acs(1,1)=1;
	*acs(2,1)=1;
	*acs(0,2)=1;
	*acs(1,2)=1;
	showBox();
	printf("Neighbors:(%d)\n",neighbors(0,0));
	/* iterate(); */
	/* showBox(); */
	/* for(;;nanosleep(&tim,NULL)) { */
	/* 	showBox(); */
	/* 	iterate(); */
	/* } */
	return 0;
}

