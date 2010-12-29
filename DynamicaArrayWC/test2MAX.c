#include <stdio.h>
#include <string.h>
#include <time.h>

#include "DynamicArrayWC.h"

#define MIN     100000
#define MAX     1000000
#define STEP    100000
#define RATE    2.0

#define COL1    "# expand  "
#define COL2    "growth rate  "
#define COL3    "max op time 1 (msec)  "
#define COL4    "max op time 2 (msec)  "
#define COL5    "max op time 3 (msec)  "

int main(){

    int n;
    double TOT1=0; double TOT2=0; double TOT3=0;
    int fc=0; int RATE_ES;
    
	do{
		printf("\ninserisci il rate di shrink ogni expand (tra 1 e 10000)\n\n");
		scanf("%d", &RATE_ES);
		if(RATE_ES<2 || RATE_ES>10000){
			printf("valore non ammesso!");
			fc=-1;
		}
		else fc=1;
	}while(fc==-1);
	printf("\n");

    /* print header */
    printf("%-*s %-*s %-*s %-*s %-*s\n", 
        strlen(COL1), COL1, 
        strlen(COL2), COL2, 
        strlen(COL3), COL3, 
        strlen(COL4), COL4,
        strlen(COL5), COL5
    );

    
    for (n = MIN; n <= MAX; n += STEP) {

        int i;
        unsigned long theStart;
        double theMaxDuration1 = 0.0,  theMaxDuration2 = 0.0,  theMaxDuration3 = 0.0;

        DynamicArrayWC** theArray;
        
        /* ------------------- run 1 ------------------- */
        theArray = DynamicArrayWC_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        for (i = 0; i < n; ++i) {
            double theOpDuration;
            unsigned long theOpStart = clock();
            if(i%RATE_ES != 0 || i==0) expand(theArray);
            else shrink(theArray);
            theOpDuration = (double)(clock() - theOpStart) / CLOCKS_PER_SEC * 1000;
            if (theOpDuration > theMaxDuration1) theMaxDuration1 = theOpDuration;
            TOT1+=theOpDuration;
        }

        deleteWC(theArray);
        
        /* ------------------- run 2 ------------------- */
        theArray = DynamicArrayWC_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        for (i = 0; i < n; ++i) {
            double theOpDuration;
            unsigned long theOpStart = clock();
            if(i%RATE_ES != 0 || i==0) expand(theArray);
            else shrink(theArray);
            theOpDuration = (double)(clock() - theOpStart) / CLOCKS_PER_SEC * 1000;
            if (theOpDuration > theMaxDuration2) theMaxDuration2 = theOpDuration;
            TOT2+=theOpDuration;
        }

        deleteWC(theArray);
        
        /* ------------------- run 3 ------------------- */
        theArray = DynamicArrayWC_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        for (i = 0; i < n; ++i) {
            double theOpDuration;
            unsigned long theOpStart = clock();
            if(i%RATE_ES != 0 || i==0) expand(theArray);
            else shrink(theArray);
            theOpDuration = (double)(clock() - theOpStart) / CLOCKS_PER_SEC * 1000;
            if (theOpDuration > theMaxDuration3) theMaxDuration3 = theOpDuration;
            TOT3+=theOpDuration;
        }

        deleteWC(theArray);

        /* print row */
        printf("%-*lu %-*f %-*f %-*f %-*f\n", 
            strlen(COL1), n, 
            strlen(COL2), RATE, 
            strlen(COL3), theMaxDuration1, 
            strlen(COL4), theMaxDuration2, 
            strlen(COL5), theMaxDuration3 
        );
    }
    
    printf("\nTOT1 = %f\nTOT2 = %f\nTOT3 = %f\nMEDIA = %f\n\n",TOT1,TOT2,TOT3,(TOT1+TOT2+TOT3)/3);
    
    return 0;
        
Err:
    fprintf(stderr, "Error in main\n");
    return 1;
}
