#include <stdlib.h>
#include <string.h>

#include "DynamicArray.h"

#define INITIAL_MAX_ITEMS    16
#define USE_REALLOC          0

//costo O(n), e ammortizzato O(1)

struct DynamicArray {
    unsigned long mItemSize;
    unsigned long mNumItems;
    unsigned long mMaxItems;
    double        mRate;
    char*         mArray;
};

DynamicArray* DynamicArray_New(unsigned long inItemSize, double inRate) {

    DynamicArray* This = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (!This) goto Err;

    This->mItemSize = inItemSize;
    This->mRate     = inRate;
    This->mNumItems = 0;
    This->mMaxItems = INITIAL_MAX_ITEMS;
    This->mArray    = (char*)malloc(INITIAL_MAX_ITEMS * inItemSize);
    if (!This->mArray) goto Err;

    return This;

Err:
    if (This) free(This);
    return NULL;
}

void DynamicArray_Delete(DynamicArray* This) {
    free(This->mArray);
    free(This);
}

void DynamicArray_Expand(DynamicArray* This) {

    This->mNumItems++;
    
    if (This->mNumItems > This->mMaxItems) {
    
        unsigned long theNewMaxItems = This->mMaxItems * This->mRate;    

        if (theNewMaxItems <= This->mMaxItems) theNewMaxItems = This->mMaxItems + 1;

        #if USE_REALLOC
        This->mArray = realloc(This->mArray, This->mItemSize*theNewMaxItems);
        #else
        {
            void* theNewArray = malloc(This->mItemSize*theNewMaxItems);
            memcpy(theNewArray, This->mArray, This->mItemSize*This->mMaxItems);
            free(This->mArray);
            This->mArray = theNewArray;
        }
        #endif

        This->mMaxItems = theNewMaxItems;
    }
}

void DynamicArray_Shrink(DynamicArray* This) {
    if (This->mNumItems > 0) This->mNumItems--;
}

void DynamicArray_SetItem(DynamicArray* This, unsigned long inIdx, void* inItemBuf) {
    if (inIdx >= This->mNumItems) return;
    memcpy(inItemBuf, This->mArray + This->mItemSize*inIdx, This->mItemSize);
}

void DynamicArray_GetItem(DynamicArray* This, unsigned long inIdx, void* outItemBuf){
    if (inIdx >= This->mNumItems) return;
    memcpy(This->mArray + This->mItemSize*inIdx, outItemBuf, This->mItemSize);
}

