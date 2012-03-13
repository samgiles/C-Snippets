/**
 * Copyright (C) 2012 Samuel Giles
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the 
 * Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * MemoryManager.h
 *
 * Defines the interface for the memory manager.
 * Version 0.1
 **/


// Include stdlib if not already.
#ifndef STDLIB_H
#include <stdlib.h>
#define STDLIB_H
#endif

#include "Ext.h"

#define MAX_STORES 5

/**
 * Defines a block of memory
 */
typedef struct mem_block {
  void* memory;
  size_t blocksize;
} MEM_BLOCK;

/**
 * Defines a block of storage.
 */
typedef struct storage_block {
  struct mem_block* memory;
  unsigned int refcount;
  struct storage_block* next;
} STORE_BLOCK;

/**
 * Defines an area of storage, the memory manager will manage the storage areas and determine where to allocate memory to.
 */
typedef struct storage_area {
  STORE_BLOCK* head;
  unsigned int count;
  struct storage_area*  next;

  union node {
    struct mem_manager*  manager;
    struct storage_area* area;
  } prev;

} STORE_AREA;

struct mem_manager {
  STORE_AREA* areas;
  unsigned int area_count;
};

struct mem_manager* memory_manager = NULL;

BOOL initialise_manager();

// Increases the number of store areas in the array by one.
STORE_AREA* increase_store_areas();

BOOL free_storage_area(STORE_AREA* area);


/**
 * Explicitly ask for some memory space.
 */
MEM_BLOCK*  mm_alloc(size_t size);

/**
 * Explicitly free memory.
 */
void mm_free(MEM_BLOCK* block);

/**
 * creates a new storage area and adds it to the memory manager. returns the storage area index in the memory manager.
 */
STORE_AREA* create_storage_area();

/**
 * De-allocates an entire storage area and removes it from the memory manager.
 */
BOOL remove_storage_area(STORE_AREA* area);

STORE_BLOCK* create_storage_block(STORE_AREA* store_area);

void* emalloc(unsigned size);

void *emalloc(unsigned size)
{
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "Out of memory!\n");
        exit(1);
    }
    return p;
}

