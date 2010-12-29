#include <stdio.h>
#include <string.h>
#include <time.h>

#include "DynamicArray.h"

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

    int n;

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

        DynamicArray* theArray;
        
        /* ------------------- run 1 ------------------- */
        theArray = DynamicArray_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        theStart = clock();

        for (i = 0; i < n; ++i) DynamicArray_Expand(theArray);

        theDuration1 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;

        DynamicArray_Delete(theArray);

        /* ------------------- run 2 ------------------- */
        theArray = DynamicArray_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        theStart = clock();

        for (i = 0; i < n; ++i) DynamicArray_Expand(theArray);

        theDuration2 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;

        DynamicArray_Delete(theArray);

        /* ------------------- run 3 ------------------- */
        theArray = DynamicArray_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        theStart = clock();

        for (i = 0; i < n; ++i) DynamicArray_Expand(theArray);

        theDuration3 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;

        DynamicArray_Delete(theArray);

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

    return 0;
        
Err:
    fprintf(stderr, "Error in main\n");
    return 1;
}
