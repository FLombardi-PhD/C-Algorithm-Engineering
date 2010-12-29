#include <stdio.h>
#include <string.h>
#include <time.h>

#include "DynamicArrayWC.h"

#define MIN     1.001
#define MAX     5.0
#define STEP    0.1
#define N       1000000

#define COL1    "# expand"
#define COL2    "growth rate"
#define COL3    "total time (msec)"
#define COL4    "average op time (msec)"

int main(){

    double r;
    double MEDIA=0;
    int cont=0;
    
    /* print header */
    printf("%-*s %-*s %-*s %-*s\n", 
        strlen(COL1), COL1, 
        strlen(COL2), COL2, 
        strlen(COL3), COL3, 
        strlen(COL4), COL4);

    for (r = MIN; r <= MAX; r += (r - 1.0) * STEP) {
	cont++;
        int i;
        unsigned long theStart;
        double theDuration;

        DynamicArrayWC** theArray = DynamicArrayWC_New(sizeof(int), r);
        if (!theArray) goto Err;

        theStart = clock();

        for (i = 0; i < N; ++i) expand(theArray);

        theDuration = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
	MEDIA+=theDuration;
	
        /* print row */
        printf("%-*lu %-*f %-*f %-*f\n", 
            strlen(COL1), N, 
            strlen(COL2), r, 
            strlen(COL3), theDuration, 
            strlen(COL4), (double)theDuration/N);

        deleteWC(theArray);
    }

	MEDIA/=cont;
	printf("\nMEDIA = %f\n",MEDIA);

    return 0;
        
Err:
    fprintf(stderr, "Error in main\n");
    return 1;
}
