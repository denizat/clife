#include <stdio.h>
#include "view.h"
#include "state.h"

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
		printf("\n");
		printf("\n");
}

