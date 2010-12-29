#ifndef __DynamicArray__
#define __DynamicArray__

typedef struct DynamicArray DynamicArray;

DynamicArray* DynamicArray_New(unsigned long inItemSize, double inRate);
void          DynamicArray_Delete(DynamicArray* This);
void          DynamicArray_Expand(DynamicArray* This);
void          DynamicArray_Shrink(DynamicArray* This);
void          DynamicArray_SetItem(DynamicArray* This, unsigned long inIdx, void* inItemBuf);
void          DynamicArray_GetItem(DynamicArray* This, unsigned long inIdx, void* outItemBuf);

#endif
