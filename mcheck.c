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
    mcheck_meminfo meminfo = {0};
    mcheck_caller_t caller = {0};
    caller.file = file;
    caller.line = line;
    caller.func = "malloc";
    meminfo.address = p;
    meminfo.size = size;
    meminfo.caller = caller;
    mcheck_mem_list_add(mlist, meminfo);
    return p;
}

void *calloc_hook(size_t nmemb, size_t size, const char *file, int line)
{
    void *p = calloc(nmemb, size);
    char buff[128] = {0};
    mcheck_meminfo meminfo = {0};
    mcheck_caller_t caller = {0};
    caller.file = file;
    caller.line = line;
    caller.func = "calloc";
    meminfo.address = p;
    meminfo.size = nmemb*size;
    meminfo.caller = caller;
    mcheck_mem_list_add(mlist, meminfo);
    return p;
}

void *realloc_hook(void *ptr, size_t size, const char *file, int line)
{
    void *p = realloc(ptr, size);
    char buff[128] = {0};
    mcheck_meminfo meminfo = {0};
    mcheck_caller_t caller = {0};
    caller.file = file;
    caller.line = line;
    caller.func = "realloc";
    meminfo.address = p;
    meminfo.size = size;
    meminfo.caller = caller;
    mcheck_mem_list_add(mlist, meminfo);
    mcheck_mem_list_delete(mlist, ptr);
    return p;
}

void free_hook(void *p, const char *file, int line){
    mcheck_mem_list_delete(mlist, p);
    free(p);
}