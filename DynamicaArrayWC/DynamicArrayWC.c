#include <stdlib.h>
#include <string.h>
#include "DynamicArrayWC.h"

#define INITIAL_MAX_ITEMS    16

struct DynamicArrayWC {
    unsigned long mItemSize;
    unsigned long mNumItems;
    unsigned long mMaxItems;
    double        mRate;
    unsigned long*         mArray;
};

unsigned long* tempor;
unsigned long* tempor2;
unsigned long n; unsigned long h; int it=0;

#define N coppia[0]->mNumItems
#define H coppia[0]->mMaxItems

#define MIN 8

DynamicArrayWC** coppia;
DynamicArrayWC* lo;
DynamicArrayWC* hi;

DynamicArrayWC** DynamicArrayWC_New(unsigned long inItemSize, double inRate) {
    coppia = (DynamicArrayWC**)malloc(2*sizeof(DynamicArrayWC*));
        
    lo = (DynamicArrayWC*)malloc(sizeof(DynamicArrayWC));
    lo->mItemSize = inItemSize;
    lo->mRate     = inRate;
    lo->mNumItems = 0;
    lo->mMaxItems = INITIAL_MAX_ITEMS;
    lo->mArray    = (unsigned long*)malloc(INITIAL_MAX_ITEMS*inItemSize);
    h=lo->mMaxItems;
    
    hi = (DynamicArrayWC*)malloc(sizeof(DynamicArrayWC));
    hi->mItemSize = inItemSize;
    hi->mRate     = inRate;
    hi->mNumItems = 0;
    hi->mMaxItems = INITIAL_MAX_ITEMS*2;
    hi->mArray    = (unsigned long*)malloc(INITIAL_MAX_ITEMS*2*inItemSize);
        
    coppia[0] = lo;
    coppia[1] = hi;
    return coppia;

}

void deleteWC(DynamicArrayWC** coppia) {
    free(coppia[0]->mArray);
    free(coppia[0]);
    free(coppia[1]->mArray);
    free(coppia[1]);
    free(coppia);    
}

void expand(DynamicArrayWC** coppia){
	if(N >= H) {
		coppia[1]->mArray[N - H] = coppia[0]->mArray[N - H];
		coppia[1]->mNumItems++; //aggiunta
	}	
	N++;
	
	if(N > 2*H){
		H*=2;
		tempor=malloc(2*H*sizeof(unsigned long));
		free(coppia[0]->mArray);
		coppia[0]->mArray = coppia[1]->mArray;
		coppia[1]->mArray=tempor;
		coppia[1]->mMaxItems*=2;
	}
}

void shrink(DynamicArrayWC** coppia){
	N--;
	
	if(N >= H) coppia[0]->mArray[N - H] = coppia[1]->mArray[N - H];
	if(N == H && H > MIN){
		H/=2;
		tempor2=malloc(H*sizeof(unsigned long));
		free(coppia[1]->mArray);
		coppia[1]->mArray = coppia[0]->mArray;
		coppia[0]->mArray=tempor2;
		coppia[1]->mMaxItems/=2;
	}
}

void set(unsigned long i, unsigned long x, DynamicArrayWC** coppia){
	if (i<0 || i>=N) exit(1);
	
	if(N<=H || i>=N-H && i<H) { 
		coppia[0]->mArray[i] = x;
	}else { coppia[1]->mArray[i] = x;
	}
	
	
}

unsigned long get(unsigned long i, DynamicArrayWC** coppia){
	if (i<0 || i>=N) exit(1);
	
	if(N<=H || i>=N-H && i<H) return coppia[0]->mArray[i];
	else return coppia[1]->mArray[i];

}
