/* ============================================================================
 *  HeapB.c
 * ============================================================================

/* includes */
#include "HeapB.h"
#include <string.h>
#include <stdio.h>

#define DEBUG 1
#define MaxTrees 32
/* types */
struct Node;

typedef struct Node {
    struct Node* p;  /* padre */
    struct Node* fs; /* fratello successivo */
    struct Node* pf; /* primo figlio */
} Node;

struct HeapB {
    size_t        keySize;
    size_t        elemSize;
    HeapB_TComp   comp;
    Node**        v;
    int           currentSize; //aggiunta da noi
};


/* ----------------------------------------------------------------------------
 *  ristruttura
 * ----------------------------------------------------------------------------
*/
static void ristruttura(HeapB* This) {
    int i;
    for (i=0; i<MaxTrees; ++i)
        while (This->v[i] != NULL && This->v[i]->fs != NULL) {

            Node *min, *max;

            if (This->comp(This->v[i]+1, This->v[i]->fs+1) < 0) {
                min = This->v[i];
                max = This->v[i]->fs;
            }
            else {
                max = This->v[i];
                min = This->v[i]->fs;
            }

            This->v[i] = This->v[i]->fs->fs;

            max->fs = min->pf;
            min->pf = max;
            max->p  = min;

            min->fs = This->v[i+1];
            This->v[i+1] = min;
        }

    #if DEBUG == 1
    /*printf("Mappa di bit dopo ristruttura\n");
    for (i=0; i<31; ++i)
        if (This->v[i])
             printf("1 ");
        else printf("0 ");
    printf("\n\n");*/
    #endif
}

/* ----------------------------------------------------------------------------
 *  Merge
 * ----------------------------------------------------------------------------
*/


/* ----------------------------------------------------------------------------
 *  New
 * ----------------------------------------------------------------------------
*/
HeapB* HeapB_New(size_t inKeySize, size_t inElemSize, HeapB_TComp inComp){
    HeapB* This = malloc(sizeof(HeapB));

    This->keySize  = inKeySize;
    This->elemSize = inElemSize;
    This->comp     = inComp;
    This->v        = malloc(32 * sizeof(struct Node*));
    This->currentSize = 0; //aggiunta da noi

    memset(This->v, 0, 32 * sizeof(struct Node*));

    return This;
}                             


/* ----------------------------------------------------------------------------
 *  Delete
 * ----------------------------------------------------------------------------
*/
void HeapB_Delete(HeapB* This){
    /* lasciata come esercizio */
    free(This->v);
    free(This);
}


/* ----------------------------------------------------------------------------
 *  Insert
 * ----------------------------------------------------------------------------
*/
HeapB_TRif HeapB_Insert(HeapB* This, const void* inKey, const void* inElem){
    struct Node* x = malloc(sizeof(struct Node) + This->keySize + This->elemSize);
    x->p  = NULL;
    x->pf = NULL;
    memcpy(x+1, inKey, This->keySize);
    memcpy((char*)(x+1)+This->keySize, inElem, This->elemSize);
    x->fs = This->v[0];
    This->v[0] = x;
    This->currentSize++; //aggiunto da noi
    ristruttura(This);
    return x;
}


/* ----------------------------------------------------------------------------
 *  RemoveMin
 * ----------------------------------------------------------------------------
*/


void HeapB_RemoveMin(HeapB* This){
    /* lasciata come esercizio */
	int j, k;
	int i = FindMinIndex(This);
	Node* min = (Node*)HeapB_FindMin(This);
	//printf("REMOVE MIN: elimino chiave %d\n",i);
	Node* temp;
	for(k=1; k<i; k++){
		min->pf->p=NULL; //stacco il suo padre
		temp=min->pf->fs; //salvo il riferimento al fratello
		min->pf->fs=This->v[i-k];
		This->v[i-k]=min->pf;
		min->pf=temp;
	}
	This->v[i]=NULL;
	ristruttura(This);
}
/* ----------------------------------------------------------------------------
 *  FindMin
 * ----------------------------------------------------------------------------
*/
int FindMinIndex(HeapB* This){
    int i;
    int minIndex=0;
    Node* min = NULL;
    for (i=0; i<32; ++i)
        if (This->v[i] != NULL &&
            (min == NULL || This->comp(This->v[i]+1, min+1) < 0) ){
                min = This->v[i];
                minIndex=i;
         }       
    return minIndex;
}

HeapB_TRif HeapB_FindMin(HeapB* This){
    int i;
    Node* min = NULL;
    for (i=0; i<32; ++i)
        if (This->v[i] != NULL &&
            (min == NULL || This->comp(This->v[i]+1, min+1) < 0) )
                min = This->v[i];
    return min;
}


/* ----------------------------------------------------------------------------
 *  Remove
 * ----------------------------------------------------------------------------
*/
void HeapB_Remove(HeapB* This, HeapB_TRif inRif){
    /* lasciata come esercizio */
}


/* ----------------------------------------------------------------------------
 *  DecreaseKey
 * ----------------------------------------------------------------------------
*/
void HeapB_DecreaseKey(HeapB* This, HeapB_TRif inRif, const void* inNewKey){
    /* lasciata come esercizio */
}


/* ----------------------------------------------------------------------------
 *  IncreaseKey
 * ----------------------------------------------------------------------------
*/
void HeapB_IncreaseKey(HeapB* This, HeapB_TRif inRif, const void* inNewKey){
    /* lasciata come esercizio */
}


/* ----------------------------------------------------------------------------
 *  GetKey
 * ----------------------------------------------------------------------------
*/
void HeapB_GetKey(HeapB* This, HeapB_TRif inRif, void* outKey){
    Node* x = (Node*) inRif;
    memcpy(outKey, x+1, This->keySize);
}


/* ----------------------------------------------------------------------------
 *  GetElem
 * ----------------------------------------------------------------------------
*/
void HeapB_GetElem(HeapB* This, HeapB_TRif inRif, void* outElem){
    /* lasciata come esercizio */
	Node* x= (Node*) inRif;
	memcpy(outElem, x+1+This->keySize, This->elemSize);
}
