#ifndef _MCHECK_H_
#define _MCHECK_H_

#include<stddef.h>

void mcheck_initialize();
void mcheck_terminate();

void *malloc_hook(size_t size, const char *file, int line);
void free_hook(void *p, const char *file, int line);

#define malloc(size)   malloc_hook(size, __FILE__, __LINE__)
#define free(p)        free_hook(p, __FILE__, __LINE__)

#endif