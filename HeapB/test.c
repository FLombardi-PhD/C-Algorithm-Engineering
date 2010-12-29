#include "HeapB.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 10000000

int comp(const void* a, const void* b){
    if (*(float*)a < *(float*)b) return -1;
    if (*(float*)a > *(float*)b) return 1;
    return 0;
}

int main(){
    int i; unsigned long theStart;
    double theDuration1; double theDuration2;
    float minKey; HeapB_TRif minRif;
    
    HeapB* h = HeapB_New(sizeof(float), sizeof(double), comp);

    theStart = clock();
    
    for (i=0; i<MAX; i++) {
        float  key  = rand() % 100;
        double elem = i;
        HeapB_Insert(h, &key, &elem);
        //printf("inserimenti 1: inserisco chiave %f\n", key);
    }

    theDuration1 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;

    
    minRif = HeapB_FindMin(h);
    HeapB_GetKey(h, minRif, &minKey);
    //printf("\nchiave minima = %f\n", minKey);
    

/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
       
    theStart = clock();
    
    //puts("inizio sequenza mista removeMin/insert\n");   
    for (i=0; i<MAX; i++) {
        float  key  = rand() % 100;
        float scelta = rand() % 2;
        double elem = i;
        if(scelta==0) {
        	HeapB_Insert(h, &key, &elem); //operazione randomica
        	//printf("\nINSERT: inserita chiave %f\n", key);
        }	
        else{
        	HeapB_RemoveMin(h);
        	minRif = HeapB_FindMin(h);
		HeapB_GetKey(h, minRif, &minKey);
		//printf("\nfine REMOVE MIN; nuova chiave minima: %f\n", minKey);
	}
    }
    
    theDuration2 = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
    
/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/
      
    printf("tempo per solo insert: %f msec\ntempo per insert/removemin: %f msec\n\n",
    	theDuration1, theDuration2);	
}
