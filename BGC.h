#ifndef _KLEVH_GARBAGE_COLLECTOR_
#define _KLEVH_GARBAGE_COLLECTOR_

#include <stdio.h>
#include <stdlib.h>

typedef struct cell{
  void * object;
  size_t size;
  struct cell * next;
}cell_t;

/**
 * @brief the linked list of cells, it is not sorted as it is (I think) more performant. Without sort, adding will be with a complexity of O(1) while removing O(n). With sort, it will be adding with O(n) and removing O(n). Even though the sorted O(n) removing is quicker than the not-sorted O(n) removing, in average it is slower (adding + removing).
 */
extern cell_t * _BGCollector; 

/**
 * @brief allocate a block of size 'size'
 * @param size : size of the block to be allocated
 * @return The newly allocated block or NULL if it failed
 */
void * mallocBGC(size_t size);

/**
 * @brief free a memory block
 * @param object : memory block to be freed
 * @return 0 if all went alright, 1 if not
 */
int freeBGC(void * object);

/**
 * @brief reallocate an already existing block
 * @param object : block to be reallocated
 * @param size : size of the new block
 * @return the newly allocated block or NULL if it failed
 */
void * reallocBGC(void * object,size_t size);

/**
 * @brief allocate a memory block and initialize all bytes to 0
 * @param nmemb : number of blocks to allocate (in a contiguous space)
 * @param size : size of each block
 * @return the newly allocated block or NULL if it failed
 */
void * callocBGC(size_t nmemb, size_t size);

/**
 * @brief tells wether or not a block was allocated using this garbage collector
 * @param object : object to be tested
 * @return 1 if the object was allocated this way, 0 if not
 */
int isAllocatedBGC(void * object);

/**
 * @brief free all allocated blocks using BGC's functions
 */
void cleanBGC();
#endif
