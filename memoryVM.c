#include <stdlib.h>
#include "memoryVM.h"

typedef struct AO
{
    void *pointer;
    int amount;
    int size;
    char type;
} AO;

AO *structs;
int lengthOfStructs;







bool initVM()
{
    lengthOfStructs = 2;
    structs = calloc(lengthOfStructs, sizeof(AO));
    if (structs == NULL) {
        return 0;
    }
    return 1;
}

void clearVM()
{
    for (int i = 0; i < lengthOfStructs; i++) {
        if (structs[i].amount <= 0) {
            free(structs[i].pointer);
        }
    }
    free(structs);
}

bool enlargeStructs(int index)
{
    lengthOfStructs = lengthOfStructs + lengthOfStructs;
    void *tempStructs = structs;
    structs = realloc(structs, lengthOfStructs * sizeof(AO));
    if (structs == NULL) {
        structs = (AO *)tempStructs;
        lengthOfStructs = lengthOfStructs / 2;
        return 0;
    }
    for (int i = index; i < lengthOfStructs; i++) {
        structs[i].pointer = 0;
        structs[i].size = 0;
        structs[i].amount = 0;
    }
    return 1;
}

int saveIntoStruct(void *thePointer, size_t size, char type)
{
    int i = 0;
    while (i < lengthOfStructs) {
        if (i == lengthOfStructs - 1) {
            if (!enlargeStructs(i + 1)) {
                return -1;
            }
        }
        if (structs[i].pointer != 0) {
            i++;
            continue;
        }
        structs[i].pointer = thePointer;
        structs[i].amount = 1;
        structs[i].size = size;
        structs[i].type = type;
        return i;
    }
    return -1;
}
void *allocateArray(size_t elementSize, size_t elementCount)
{
    void *thePointer = calloc(elementCount, elementSize);
    if (thePointer == NULL) {
        return NULL;
    }
    int done = saveIntoStruct(thePointer, elementCount * elementSize, 'j');
    if (done == -1) {
        free(thePointer);
        return NULL;
    }
    return thePointer;
}

void *allocate(size_t size)
{
    void *thePointer = calloc(size, 1);
    if (thePointer == NULL) {
        return NULL;
    }
    int done = saveIntoStruct(thePointer, size, 'j');
    if (done == -1) {
        free(thePointer);
        return NULL;
    }
    return thePointer;
}
void acquire(void *memory)
{
    int i = 0;
    while (i < lengthOfStructs) {
        if (structs[i].pointer != memory) {
            i++;
            continue;
        }
        if (structs[i].type == 'd') {
            acquireArray2D(memory);
            return;
        }
        structs[i].amount++;
        return;
    }
    return;
}

int destroyMemory(void *memory, int index)
{
    int i;
    if (index == -1) {
        i = 0;
    } else {
        i = index;
    }
    while (i < lengthOfStructs) {
        if (structs[i].pointer != memory) {
            i++;
            continue;
        }
        structs[i].pointer = 0;
        structs[i].amount = 0;
        structs[i].size = 0;
        free(memory);
        return 1;
    }
    return 0;
}

bool release(void *memory)
{
    int i = 0;
    while (i < lengthOfStructs) {
        if (structs[i].pointer != memory) {
            i++;
            continue;
        }
        if (structs[i].type == 'd') {
            return releaseArray2D(memory);
        }
        structs[i].amount--;
        if (structs[i].amount <= 0) {
            destroyMemory(memory, i);
            return 1;
        }
        return 0;
    }
    return 0;
}

void *allocateSubArray(size_t elementSize, size_t elementCount, int *smallArrayIndexes, int index)
{
    void *thePointer = calloc(elementCount, elementSize);
    if (thePointer == NULL) {
        return NULL;
    }
    int done = saveIntoStruct(thePointer, elementCount * elementSize, 'j');
    if (done == -1) {
        free(thePointer);
        return NULL;
    }
    smallArrayIndexes[index] = done;
    return thePointer;
}
void **allocateSuperArray(size_t elementSize, size_t elementCount)
{
    void **thePointer = calloc(elementCount, elementSize);
    int done = saveIntoStruct(thePointer, elementCount * elementSize, 'd');
    if (done == -1) {
        free(thePointer);
        return NULL;
    }
    return thePointer;

}
void allocateArray2DFAILED(int *smallArraysIndexes, void **thePointer, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        destroyMemory(thePointer[i], smallArraysIndexes[i]);
    }
    int i = 0;
    while (i < lengthOfStructs) {
        if (structs[i].pointer != thePointer) {
            i++;
            continue;
        }
        structs[i].pointer = 0;
        structs[i].amount = 0;
        structs[i].size = 0;
        free(thePointer);
        return;
    }
}
void **allocateArray2D(size_t elementSize, size_t subarrays, size_t *elementCounts)
{

    void **thePointer = allocateSuperArray(sizeof(void *), subarrays);
    if (thePointer == NULL) {
        return NULL;
    }
    int *smallArraysIndexes = calloc(subarrays, sizeof(int));
    if (smallArraysIndexes == NULL) {
        destroyMemory(thePointer, -1);
        return NULL;
    }
    int length;
    for (size_t i = 0; i < subarrays; i++) {
        //dávat pozor na to když to nevýjde
        if (elementCounts == NULL) {
            length = subarrays;
        } else {
            length = elementCounts[i];
        }
        thePointer[i] = allocateSubArray(elementSize, length, smallArraysIndexes, i);
        if (thePointer[i] == NULL) {
            allocateArray2DFAILED(smallArraysIndexes, thePointer, i);
            free(smallArraysIndexes);
            return NULL;
        }
    }
    free(smallArraysIndexes);
    return thePointer;
}
void acquireAllTheNanoArrays(void **array, int size)
{
    for (int i = 0; i < size; i++) {
        if (array[i] == NULL) {
            continue;
        }

        acquire(array[i]);

    }
}
void acquireArray2D(void **array)
{
    int i = 0;
    while (i < lengthOfStructs) {
        if (structs[i].pointer != array) {
            i++;
            continue;
        }
        structs[i].amount++;
        acquireAllTheNanoArrays(array, structs[i].size / sizeof(void *));
        return;
    }
    return;
}
void releaseAllTheNanoArrays(void **array, int size)
{
    for (int i = 0; i < size; i++) {
        if (array[i] == NULL) {
            continue;
        }
        if (release(array[i])) {
            array[i] = NULL;
        }
    }
}
bool releaseArray2D(void **array)
{
    int i = 0;
    while (i < lengthOfStructs) {
        if (structs[i].pointer != array) {
            i++;
            continue;
        }
        structs[i].amount--;
        releaseAllTheNanoArrays(array, structs[i].size / sizeof(void *));
        if (structs[i].amount <= 0) {
            destroyMemory(array, i);
            return 1;
        }
        return 0;
    }
    return 0;
}

