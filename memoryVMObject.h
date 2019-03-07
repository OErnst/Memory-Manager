#ifndef MEMORYVMOBJECT_H
#define	MEMORYVMOBJECT_H

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
#include "dataDef.h"

/**
 * Allocates and initializes an object described by the definition "def".
 * The initialization is handled by the constructor function.
 *
 * @note        Should the constructor fail, the memory shall be deallocated
 *              and the function shall return NULL.
 *
 * @param   def     definition of the object
 * @returns pointer to the object or NULL on failure
 */
void* allocateNew0(dataDef0* def);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Same as allocateNew0 but for objects with constructor of arity 1.
 *
 * @param   def     definition of the object
 * @param   param1  constructor parameter
 * @returns pointer to the object or NULL on failure
 */
void* allocateNew1(dataDef1* def, void* param1);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Same as allocateNew0 but for objects with constructor of arity 2.
 *
 * @param   def     definition of the object
 * @param   param1  constructor parameter
 * @param   param2  constructor parameter
 * @returns pointer to the object or NULL on failure
 */
void* allocateNew2(dataDef2* def, void* param1, void* param2);

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Creates a data definition for an object. The definition shall be managed
 * by the MVM, so that acquire and release should work on the return
 * value of this function unless NULL is returned.
 * The object shall be constructed with the allocateNew0 function.
 *
 * @param   size    size of the object
 * @param   ctor    constructor function
 * @param   dtor    destructor function
 * @returns data definition pointer
 */
dataDef0* createDataDef0(size_t size, bool(*ctor)(void*),
                                      void(*dtor)(void*));
/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Creates a data definition for an object. The definition shall be managed
 * by the MVM, so that acquire and release should work on the return
 * value of this function unless NULL is returned.
 * The object shall be constructed with the allocateNew1 function.
 *
 * @param   size    size of the object
 * @param   ctor    constructor function
 * @param   dtor    destructor function
 * @returns data definition pointer
 */
dataDef1* createDataDef1(size_t size, bool(*ctor)(void*, void*),
                                      void(*dtor)(void*));

/*****************************************************************************/
/*  DO NOT MODIFY THIS FILE!                                                 */
/*****************************************************************************/

/**
 * Creates a data definition for an object. The definition shall be managed
 * by the MVM, so that acquire and release should work on the return
 * value of this function unless NULL is returned.
 * The object shall be constructed with the allocateNew1 function.
 *
 * @param   size    size of the object
 * @param   ctor    constructor function
 * @param   dtor    destructor function
 * @returns data definition pointer
 */
dataDef2* createDataDef2(size_t size, bool(*ctor)(void*, void*, void*),
                                      void(*dtor)(void*));

#endif	/* MEMORYVMOBJECT_H */
