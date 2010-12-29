#include "HeapB.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int comp(const void* a, const void* b){
    if (*(float*)a < *(float*)b) return -1;
    if (*(float*)a > *(float*)b) return 1;
    return 0;
}

int main(){
    int i;
    HeapB* h = HeapB_New(sizeof(float), sizeof(double), comp);

    srand(clock());

    for (i=0; i<10; i++) {
        float  key  = rand() % 100;
        double elem = i;
        HeapB_Insert(h, &key, &elem);
        printf("inserita chiave %f\n", key);
    }


    {
        float minKey;
        HeapB_TRif minRif;
        minRif = HeapB_FindMin(h);
        HeapB_GetKey(h, minRif, &minKey);
        printf("chiave minima = %f\n", minKey);
    }
}