#include <stdio.h>
#include <string.h>
#include <time.h>
#include "DynamicArrayWC.h"

#define RATE    2.0

void sel_sort(DynamicArrayWC** theArray, unsigned long n){

unsigned long j, l, p, minimo;

for (j=0; j<n-1; j++) {
    minimo = get(j,theArray);
    p = j;
    for (l=j+1; l<n; l++){
	if (get(l,theArray)<minimo){
                minimo = get(l,theArray);
                p = l;
            }
        }
     set(p, get(j,theArray), theArray);
     set(j, minimo, theArray);
 }
}


void merge(DynamicArrayWC** theArray, int start, int med, int end){
     int i, j, k;
     
     DynamicArrayWC** appo = DynamicArrayWC_New(sizeof(unsigned long), RATE);
     
     k=0;
     i = start;
     j = med +1;
     
     while (i<=med && j<=end){
           if (get(i,theArray)<=get(j,theArray)) {
               expand(appo);
               set(k,get(i,theArray),appo);
               i++;
           }
           else {
               expand(appo);
               set(k,get(j,theArray),appo);
               j++;
           }
           k++;          
     }
     if (i>med){
         while (j<=end){
               expand(appo);
               set(k,get(j,theArray),appo);
               j++;
               k++;
         }
     }
     else {
          while (i<=med){
              expand(appo);
              set(k,get(i,theArray),appo);
              i++;
              k++;
          }
     }
     
     //metto i valori ordinati nell'array di partenza
     k = 0;
     for (i=start; i<=end; i++){
         set(i,get(k,appo),theArray);
         k++;
     }
    
}

void mergeSort(DynamicArrayWC** theArray, unsigned long start, unsigned long end){
     if(start<end){
         unsigned long med = (start+end)/2;
         mergeSort(theArray, start, med);
         mergeSort(theArray, med+1, end);
         merge(theArray, start, med, end);
     }
}

void sort(DynamicArrayWC** theArray, unsigned long n){
     //int med = N/2;
     mergeSort(theArray, 0, n-1);
}


void stampa(DynamicArrayWC** theArray, unsigned long k){
     int i;
     for (i=0; i<k; i++)
         printf("%lu\n", get(i,theArray));
     printf("\n");
     printf("\n");
}



int main(){

	DynamicArrayWC** theArray = DynamicArrayWC_New(sizeof(unsigned long), RATE);
	int fc=0;
	unsigned long val, tmp, min, i, k, prova;
	unsigned long theStart; 
	double theDuration;
	
	do{
		printf("\ninserisci il numero di inserimenti casuali\n\n");
		scanf("%lu", &k);
		if(k<2 || k>10000000000000){
			printf("valore non ammesso!");
			fc=-1;
		}
		else fc=1;
	}while(fc==-1);
	printf("\n");
	
	//inserimento di k numeri casuali
	for (i=0; i<k; i++) {
		expand(theArray);
		val = rand()%400;
		set(i,val,theArray);
		//prova = get(i,theArray);
		//printf("%lu\n",prova);
	}
	
	//printf("\n");
	//printf("CIAOOOOO\n");
	
	//--------------RUN 1-----------------------
	
	
	theStart = clock();
	
	min = 999999;
	for (i=0; i<k; i++) {
		tmp = get(i,theArray);
		//printf("%lu\n",tmp);
		if(tmp<=min) min = tmp;
	}
    	printf("minimo: %lu\n",min);
    	
    	theDuration = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
    	printf("tempo per trovare il minimo: %f\n",theDuration);
    	
    	
    	//-------------RUN 2-------------------------
    	
    	/*
    	theStart = clock();
    	sel_sort(theArray, k);
    	theDuration = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
    	printf("tempo per ordinare l'array con Selection Sort: %f\n",theDuration);
    	*/
    	
    	
    	//-------------RUN 3--------------------------
    	
    	theStart = clock();
    	sort(theArray, k);
    	theDuration = (double)(clock() - theStart) / CLOCKS_PER_SEC * 1000;
    	//stampa(theArray, k);
    	printf("tempo per ordinare l'array con Merge Sort: %f\n",theDuration);    	
}



