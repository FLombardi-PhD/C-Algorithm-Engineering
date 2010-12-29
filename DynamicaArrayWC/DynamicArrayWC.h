#ifndef __DynamicArrayWC__
#define __DynamicArrayWC__

typedef struct DynamicArrayWC DynamicArrayWC;
 
DynamicArrayWC** DynamicArrayWC_New(unsigned long inItemSize, double inRate);
void          deleteWC(DynamicArrayWC**);
void          expand(DynamicArrayWC**);
void          shrink();
void          set(unsigned long i, unsigned long x, DynamicArrayWC**);
unsigned long          get(unsigned long i, DynamicArrayWC**);

#endif
