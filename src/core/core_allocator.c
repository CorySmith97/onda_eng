
/*
 * Global Allocator Interface
 */

#ifdef DEBUG
TrackingAllocator GLOBAL_ALLOCATOR;
#else
PageAllocator GLOBAL_ALLOCATOR;
#endif


void *paalloc(PageAllocator*, size_t);
void pafree(PageAllocator*);

void *aaalloc(ArenaAllocator*, size_t);
void aafree(ArenaAllocator*);
