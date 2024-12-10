#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *aligned_malloc(size_t size, size_t alignment) {
  if((alignment == 0) || ((alignment & (alignment-1)) != 0))
    return NULL;
  
  size_t ptr_sz = sizeof(void *);
  void *base_ptr = malloc(size + alignment-1 + ptr_sz);
  if(base_ptr == NULL) {
    return NULL;
  }
  printf("base ptr: %p\n", base_ptr);
  void *algnd_ptr = (void *)(((uintptr_t)base_ptr + alignment-1 + ptr_sz) & (~(alignment-1)));
  ((void **)algnd_ptr)[-1] = base_ptr;
  // *((void **)algnd_ptr - 1) = base_ptr;

  return algnd_ptr;
}

void aligned_free(void *aligned_ptr){
  // void *base_ptr = *((void**)aligned_ptr - 1);
  void *base_ptr = ((void **)aligned_ptr)[-1];
  printf("Freeing: %p\n\n", base_ptr);
  free(base_ptr);
}

int main() {

  size_t algn = 1 << 8; void *aptr;
  for(int ix=0; ix<10; ix++)
  {
    // void *aptr = malloc(123);
    // printf("Aligned to %u ptr: %p\n", 0, aptr);
    // free(aptr);

    aptr = aligned_malloc(123, algn);
    printf("Aligned to %zu ptr: %p %zu %zu %zu\n", algn, aptr, sizeof(void *), sizeof(uintptr_t), sizeof(size_t));
    aligned_free(aptr);
  }
  return 0;
}
