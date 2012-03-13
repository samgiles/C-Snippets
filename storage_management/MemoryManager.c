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
 * MemoryManager.c
 *
 * Defines the interface for the memory manager.
 * Version 0.1
 **/
#include <stdio.h>
#include "MemoryManager.h"



MEM_BLOCK*  mm_alloc(size_t size) {
  initialise_manager();
  STORE_AREA* area = NULL;

  if (memory_manager->area_count == 0) {
    area = create_storage_area();
    
    
  }


  printf("Store Count: %d", memory_manager->area_count);
}

/**
 * creates a new storage area and adds it to the memory manager. returns the storage area index in the memory manager.
 */
STORE_AREA* create_storage_area() {

  if (memory_manager->areas == NULL) {
    // Init head of the linked list inside the memory_manager
    memory_manager->areas = (STORE_AREA*)emalloc(sizeof(STORE_AREA));

    memory_manager->areas->prev.manager = memory_manager;
    memory_manager->areas->head = NULL;
    memory_manager->areas->next = NULL;

    memory_manager->area_count = 1;
    return memory_manager->areas;
  } else {
    return increase_store_areas();
  }
}

STORE_AREA* increase_store_areas() {

  if (memory_manager->area_count >= MAX_STORES) {
    // We've created the maximum amount of storage areas, return -1 to notify caller.
    return FALSE;
  }
  STORE_AREA* area = memory_manager->areas;
  STORE_AREA* prev;

  while(area != NULL) {
    prev = area;
    area = area->next;
  }
 
  area = (STORE_AREA*)emalloc(sizeof(STORE_AREA));
  area->prev.area = prev;
  area->head = NULL;
  area->next = NULL;

  memory_manager->area_count++;

  return area;
}

/**
 * De-allocates an entire storage area and removes it from the memory manager.  calling this on a memory block will deallocate EVERYTHING inside it.
 */
BOOL remove_storage_area(STORE_AREA* area) {
    // remove from linked list.
    if (area->prev.manager == NULL) {
      area->prev.area->next = (area->next == NULL)? NULL : area->next;
    } else {
      area->prev.manager->areas = (area->next == NULL)? NULL : area->next;
    }

    if (area->next != NULL) {
       area->next->prev = area->prev;
    }
    memory_manager->area_count--;
    // Free all resources in area.
    
    
    // finally free the area.
    free(area);
    return TRUE;
}


STORE_BLOCK* create_storage_block(STORE_AREA* store_area) {
  STORE_BLOCK* block = (STORE_BLOCK*)emalloc(sizeof(STORE_BLOCK));

  // Add the new block onto the storage area. TODO:
  
  return block;
}

void mm_free(MEM_BLOCK* block) {
   // temp
   free(memory_manager);
}

BOOL initialise_manager() {
  // memory_manager has not been allocated yet.
  if (memory_manager == NULL) {
     memory_manager = (struct mem_manager*)emalloc(sizeof(struct mem_manager));
     memory_manager->area_count = 0;
     memory_manager->areas = NULL;
     return TRUE; // Initialised memory_manager.
  }

  return FALSE; // Already initialised.
}


/**
 * Keep gcc happy for the moment.
 */
int main(int argc, char* argv[]) {
  MEM_BLOCK* mem = mm_alloc(sizeof(char));
  mm_free(mem);
}
