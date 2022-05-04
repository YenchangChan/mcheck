#include<stdio.h>
#include<malloc.h>
#include "meminfo.h"

static mcheck_mem_list *mlist = NULL;

void mcheck_initialize()
{
    init_report_file();
    mcheck_mem_list_create(&mlist);
}

void mcheck_terminate(){
    mcheck_list_report_leak(mlist);
    mcheck_list_destory(mlist);
}

void *malloc_hook(size_t size, const char *file, int line)
{
    void *p = malloc(size);
    char buff[128] = {0};
    printf("%s:%d [%p]size = %lu\n", file, line, p, size);
    mcheck_meminfo meminfo = {0};
    mcheck_caller_t caller = {0};
    caller.file = file;
    caller.line = line;
    meminfo.address = p;
    meminfo.size = size;
    meminfo.caller = caller;
    mcheck_mem_list_add(mlist, meminfo);
    return p;
}

void free_hook(void *p, const char *file, int line){
    mcheck_mem_list_delete(mlist, p);
    free(p);
}