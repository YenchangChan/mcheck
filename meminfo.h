#ifndef _MEMINFO_H_
#define _MEMINFO_H_

#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>

typedef enum mcheck_errcode_t
{
    MCHECK_SUCCESS,
    MCHECK_FAILED,
}mcheck_errcode_t;

typedef struct mcheck_caller_t
{
    const char *file;
    int line;
    const char *func;
} mcheck_caller_t;

typedef struct mcheck_meminfo {
    void    *address;
    size_t  size;
    mcheck_caller_t caller;
}mcheck_meminfo;

typedef struct mcheck_mem_list {
    mcheck_meminfo mem_info;
    struct mcheck_mem_list *next;
}mcheck_mem_list;

int mcheck_mem_list_create(mcheck_mem_list **list);
int mcheck_mem_list_add(mcheck_mem_list *mlist, mcheck_meminfo mem_info);
mcheck_mem_list *mcheck_mem_list_get(mcheck_mem_list *mlist, void *address);
int mcheck_mem_list_delete(mcheck_mem_list *mlist, void *address);
int mcheck_list_size(mcheck_mem_list *mlist);
void mcheck_list_report_leak(mcheck_mem_list *mlist);
void mcheck_list_destory(mcheck_mem_list *mlist);
void init_report_file();

#endif