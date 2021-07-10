#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
Todo: change acs to set, allocate tmp diff as the same size as box and just have an instruction counter instead of realloc each time.
*/


int BOX_SIZE;
int *box;

int* acs(int x, int y) {
	return &box[x*BOX_SIZE+y];
}
int view(int x, int y)
{
	return box[x*BOX_SIZE + y];
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
			if(view(i,k) == 1)
				printf("8|");
			else
				printf(" |");
		}
		printf("\n");
	}
	href();
	printf("\n");
	printf("\n");
}



void
clearBox()
{
	for(int i =0; i<BOX_SIZE;i++){
		for(int k=0;k<BOX_SIZE;k++) {
			*acs(i,k) = 0;
		}
	}
}

int SNEED;

void
randBox()
{
	srand(SNEED);
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

typedef struct {
	int x;
	int y;
	int to;
} todo;
todo *tmp;
int tmpsize;

void
iterate() {
	tmpsize=0;
	int n;
	for(int i = 0; i<BOX_SIZE;i++) {
		for(int k=0;k<BOX_SIZE;k++){
			n = neighbors(i,k);
			if(view(i,k)) {
				if(!(n==2 || n==3)) {
					/* printf("Death at(%d,%d)\tNeighbors:(%d)\n",i,k,n); */
					/* *acs(i,k) = 0; */
					tmp[tmpsize].x = i;
					tmp[tmpsize].y = k;
					tmp[tmpsize].to = 0;
					tmpsize++;
				}

			} else {
				if(n == 3){
					/* printf("Life at(%d,%d)\tNeighbors:(%d)\n",i,k,n); */
					/* *acs(i,k) = 1; */
					tmp[tmpsize].x = i;
					tmp[tmpsize].y = k;
					tmp[tmpsize].to = 1;
					tmpsize++;

				}
			}
		}
	}
	printf("%dLEN\n",tmpsize);
	for(int i = 0; i< tmpsize;i++) {
		*acs(tmp[i].x,tmp[i].y) = tmp[i].to;
		/* printf("i->%d, x->%d, y->%d, to->%d\n",i,tmp[i].x,tmp[i].y,tmp[i].to); */
	}
}



int
main(int argv, char **argc) {
	if(argv < 2) {
		printf("Please give me a box size\n");
		return 1;
	}
	SNEED = atoi(argc[2]);
	BOX_SIZE = atoi(argc[1]);
	box = (int *)malloc(BOX_SIZE*BOX_SIZE*sizeof(int));
	tmp = (todo *)malloc(BOX_SIZE*BOX_SIZE*sizeof(todo));
	struct timespec tim;
	/* tim.tv_sec = 1; */
	tim.tv_nsec = 50000000L;
	/* tim.tv_nsec = 100000000L; */
	/* tim.tv_nsec = 100000000L; */
	/* randBox(); */
	*acs(0,0)=1;
	*acs(1,1)=1;
	*acs(2,1)=1;
	*acs(0,2)=1;
	*acs(1,2)=1;
	/* randBox(); */
	/* showBox(); */
	for(;;nanosleep(&tim,NULL)) {
		showBox();
		iterate();
	}
	free(tmp);
	free(box);
	return 0;
}

