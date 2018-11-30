/*
Rick Franc
ECE 154A - Fall 2018
Lab 6 - Mystery Caches
Due: 12/7/18, 11:00 pm

Mystery Cache Geometries:

Cache size: 4194304 bytes
Cache associativity: 16
Cache block size: 64 bytes
gcc -Wall cache-test-skel.c mystery1.o -o cache-test -m32
Cache size: 4096 bytes
Cache associativity: 1
Cache block size: 4 bytes
gcc -Wall cache-test-skel.c mystery2.o -o cache-test -m32
Cache size: 4096 bytes
Cache associativity: 128
Cache block size: 32 bytes

mystery0:
    block size = 64 bytes 
    cache size = 4194304 bytes
    associativity = 16
mystery1:
    block size = 4 bytes
    cache size = 4096 bytes
    associativity = 1
mystery2:
    block size = 32 bytes
    cache size = 4096 bytes
    associativity = 128
*/

#include <stdlib.h>
#include <stdio.h>

#include "mystery-cache.h"

/* 
   Returns the size (in B) of the cache
*/
int get_cache_size(int block_size) {
  access_cache(0);
  addr_t max_index = 1;
  while(1){
    for(addr_t i = 0; i <= max_index; i++){
      access_cache(i*block_size);
    }
    if(access_cache(0) == FALSE){
      return max_index*block_size;
    }
    max_index++;
  }
}

/*
   Returns the associativity of the cache
*/
int get_cache_assoc(int size) {
  access_cache(0);
  addr_t max_index = 1;
  while(1){
    for(addr_t i = 0; i <= max_index; i++){
      access_cache(i*size);
    }
    if(access_cache(0) == FALSE){
      return max_index;
    }
    max_index++;
  }
}

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size() {
  access_cache(0);
  addr_t index = 1;
  while(access_cache(index) == TRUE){
    index++;
  }
  return index;
}

int main(void) {
  int size;
  int assoc;
  int block_size;
  
  /* The cache needs to be initialized, but the parameters will be
     ignored by the mystery caches, as they are hard coded.
     You can test your geometry paramter discovery routines by 
     calling cache_init() w/ your own size and block size values. */
  cache_init(0,0);
  
  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);


  printf("Cache size: %d bytes\n",size);
  printf("Cache associativity: %d\n",assoc);
  printf("Cache block size: %d bytes\n",block_size);
  
  return EXIT_SUCCESS;
}
