#ifndef MEMORYVM_H
#define	MEMORYVM_H

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/*
 * Our automated tests will use THE ORIGINAL version of this file.
 * If you modify yours, the program  MAY FAIL to compile when submitted
 * or will not run correctly.
 *
 *
 *                          YOU HAVE BEEN WARNED!
 */

/*****************************************************************************/

#include <stdbool.h>

/**
 * Initializes the Memory Virtual Machine (henceforth MVM).
 * This is the place where you can initialize the global structure,
 * if you solution needs one.
 *
 * @note    In case of failure this function MUST deallocate all memory
 *          it allocated to the point something went wrong!
 *
 * @returns true success, false otherwise
 */
bool initVM(void);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Releases all the memory used by the instance of MVM.
 * After this function ends, there should be no blocks of memory
 * with reference counter equal to zero. All other blocks must remain
 * valid.
 */
void clearVM(void);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Tries to allocate memory chunk of size "size".
 *
 * @note    If the allocation succeeds, the memory returned shall be
 *          zero initialized!
 * @note    The initial reference counter shall be set to 1.
 *
 * @param   size        size of the memory chunk to allocate, in bytes
 * @returns pointer to the allocated memory or NULL on failure
 */
void* allocate(size_t size);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Allocates an array of elementCount elements, each of size elementSize.
 *
 * @note    If the allocation succeeds, the memory returned shall be
 *          zero initialized!
 * @note    The initial reference counter shall be set to 1.
 *
 * @param   elementSize     size of a single element
 * @param   elementCount    number of elements
 * @return  pointer to the allocated memory or NULL on failure
 */
void* allocateArray(size_t elementSize, size_t elementCount);

/**
 * Allocates an irregular array of arrays. The number of subarrays
 * is given in the "subarrays" parameter, sizes of each individual subarray
 * is hence specified in the "elementCounts" parameter.
 *
 * That is, the outer array shall have "subarrays" elements, while each
 * inner array on index "n" (n between 0 to subarrays exclusive) is
 * "elementsCount[n]" elements long.
 *
 * Inner elements are "elementSize" bytes long.
 *
 * In a special case, if "elementCounts" is NULL, a square matrix shall be
 * created, that is, each subarray shall be "subarrays" elements long.
 *
 * @note    If the allocation succeeds, the memory of each subarray
 *          shall be zero initialized!
 * @note    The initial reference counter of the outer array and all
 *          inner arrays shall be set to 1.
 * @note    Should allocation of ANY inner array fail, the function shall
 *          release ALL acquired memory and return NULL.
 *
 * @param   elementSize     size of a single element
 * @param   subarrays       number of inner arrays
 * @param   elementCounts   sizes of inner arrays
 * @return  pointer to the outer array of NULL on failure
 */
void** allocateArray2D(size_t elementSize, size_t subarrays, size_t* elementCounts);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Increments the reference counter of the given memory block.
 * Should also work for arrays. The behavior on pointers not returned from
 * functions of the "allocate" family is undefined.
 *
 * @param   memory      pointer to the memory block
 */
void acquire(void* memory);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Increments the reference counter of the given outer array and
 * all its inner arrays. The behavior on pointers not returned from
 * functions of the "allocate" family is undefined.
 *
 * @param   array       array pointer
 */
void acquireArray2D(void** array);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Decrements the reference counter of the given memory block.
 *
 * @param   memory  pointer to the memory block
 * @return  true if the reference counter reached zero, false otherwise
 */
bool release(void* memory);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Decrements the reference counter of the outer and all inner arrays.
 *
 * @param   array   pointer to the array
 * @return  true if the outer array reference counter reached zero
 */
bool releaseArray2D(void** array);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

#endif	/* MEMORYVM_H */
