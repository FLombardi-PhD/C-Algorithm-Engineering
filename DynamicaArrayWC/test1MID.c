#include <stdio.h>
#include <string.h>
#include <time.h>

#include "DynamicArrayWC.h"

#define MIN     1000000
#define MAX     10000000
#define STEP    1000000
#define RATE    2.0

#define COL1    "# expand "
#define COL2    "growth rate"
#define COL3    "tot time 1 (msec)"
#define COL4    "tot time 2 (msec)"
#define COL5    "tot time 3 (msec)"
#define COL6    "avg op time (msec)"

int main(){

    int n; int fc=0; int RATE_ES;
    double TOT1=0; double TOT2=0; double TOT3=0;

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
    printf("%-*s %-*s %-*s %-*s %-*s %-*s\n", 
        strlen(COL1), COL1, 
        strlen(COL2), COL2, 
        strlen(COL3), COL3, 
        strlen(COL4), COL4,
        strlen(COL5), COL5,
        strlen(COL6), COL6
    );

    for (n = MIN; n <= MAX; n += STEP) {

        int i;
        unsigned long theStart;
        double theDuration1, theDuration2, theDuration3;

        DynamicArrayWC** theArray; 
        
        /* ------------------- run 1 ------------------- */
        theArray = DynamicArrayWC_New(sizeof(int), RATE);
        
        theStart = clock();

        for (i = 0; i < n; ++i){
        	if(i%RATE_ES != 0 || i==0) expand(theArray);
                else shrink(theArray);
	}
	
        theDuration1 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
	TOT1+=theDuration1;
        deleteWC(theArray);
	
        /* ------------------- run 2 ------------------- */
        theArray = DynamicArrayWC_New(sizeof(int), RATE);
       
        theStart = clock();
	
        for (i = 0; i < n; ++i){
        	if(i%RATE_ES != 0 || i==0) expand(theArray);
                else shrink(theArray);
	}

        theDuration2 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
	TOT2+=theDuration2;
        deleteWC(theArray);

        /* ------------------- run 3 ------------------- */
        theArray = DynamicArrayWC_New(sizeof(int), RATE);
        

        theStart = clock();
	
        for (i = 0; i < n; ++i){
        	if(i%RATE_ES != 0 || i==0) expand(theArray);
                else shrink(theArray);
	}

        theDuration3 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
	TOT3+=theDuration3;
        deleteWC(theArray);

        /* print row */
        printf("%-*lu %-*f %-*f %-*f %-*f %-*f\n", 
            strlen(COL1), n, 
            strlen(COL2), RATE, 
            strlen(COL3), theDuration1, 
            strlen(COL4), theDuration2, 
            strlen(COL5), theDuration3, 
            strlen(COL6), ((theDuration1 + theDuration2 + theDuration3)/3)/n
        );
    }
	
	printf("\nTOT1 = %f\nTOT2 = %f\nTOT3 = %f\nMEDIA = %f\n\n",TOT1,TOT2,TOT3,(TOT1+TOT2+TOT3)/3);
        
    return 0;

}
