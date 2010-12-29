/* ============================================================================
 *  HeapB.h
 * ============================================================================

 *  Author:    (c) 2008 Camil Demetrescu
 *  License:   See the end of this file for license information
 *  Created:   November 13, 2008
 *  Module:    ae
*/

#ifndef __HeapB__
#define __HeapB__

#include <stdlib.h>

typedef struct HeapB HeapB;
typedef int  (*HeapB_TComp)(const void* a, const void* b);
typedef void*  HeapB_TRif;

HeapB*     HeapB_New         (size_t inKeySize, size_t inElemSize, HeapB_TComp inComp);
void       HeapB_Delete      (HeapB* This);

HeapB_TRif HeapB_Insert      (HeapB* This, const void* inKey, const void* inElem);
void       HeapB_RemoveMin   (HeapB* This);
HeapB_TRif HeapB_FindMin     (HeapB* This);
int        FindMinIndex      (HeapB* This);
void       HeapB_Remove      (HeapB* This, HeapB_TRif inRif);
void       HeapB_DecreaseKey (HeapB* This, HeapB_TRif inRif, const void* inNewKey);
void       HeapB_IncreaseKey (HeapB* This, HeapB_TRif inRif, const void* inNewKey);

//HeapB*     HeapB_Merge       (HeapB* inC1, HeapB* inC2);

void       HeapB_GetKey      (HeapB* This, HeapB_TRif inRif, void* outKey);
void       HeapB_GetElem     (HeapB* This, HeapB_TRif inRif, void* outElem);

#endif

/* Copyright (c) 2008 Camil Demetrescu

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
