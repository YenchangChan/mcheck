#include "meminfo.h"

int mcheck_mem_list_create(mcheck_mem_list **mlist){
    if (*mlist != NULL) {
        mcheck_list_destory(*mlist);
    }

    *mlist = (mcheck_mem_list *)calloc(1, sizeof(mcheck_mem_list));
    if (*mlist == NULL) {
        return MCHECK_FAILED;
    }
    (*mlist)->next = NULL;
    return MCHECK_SUCCESS;
}

int mcheck_mem_list_add(mcheck_mem_list *mlist, mcheck_meminfo mem_info)
{
    mcheck_mem_list *node = NULL;
    mcheck_mem_list_create(&node);
    node->mem_info = mem_info;
    if (mlist == NULL)
    {
        mlist = node;
        return MCHECK_SUCCESS;
    }
    while (mlist->next != NULL)
    {
        mlist = mlist->next;
    }
    mlist->next = node;
    return MCHECK_SUCCESS;
}

mcheck_mem_list *mcheck_mem_list_get(mcheck_mem_list *mlist, void *address){
    if (mlist == NULL) {
        return NULL;
    }
    mcheck_mem_list *node = mlist;
    while (mlist != NULL) {
        if (address == mlist->mem_info.address) {
            return node;
        }
        mlist = mlist->next;
    }
    return NULL;
}

int mcheck_mem_list_delete(mcheck_mem_list *mlist, void *address){
    if (mlist == NULL) {
        return MCHECK_FAILED;
    }

    mcheck_mem_list *current = mlist;
    mcheck_mem_list *prev = mlist;

    while (current != NULL) {
        if (current->mem_info.address == address) {
            if (mlist == current) {
                if (current->next = NULL) {
                    mlist = NULL;
                } else {
                    mlist = mlist->next;
                }
            } else {
                prev->next = current->next;
            }
            free(current);
            return MCHECK_SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    return MCHECK_FAILED;
}

int mcheck_list_size(mcheck_mem_list *mlist){
    if (mlist == NULL)   {return 0;}
    int size = 0;
    while(mlist->next != NULL)
    {
        size++;
        mlist = mlist->next;
    }
    return size;
}

void mcheck_list_destory(mcheck_mem_list *mlist){
    if (mlist == NULL) {
        return;
    }

    mcheck_mem_list *current = mlist;
    mcheck_mem_list *prev = mlist;
    while (prev != NULL) {
        current = current->next;
        free(prev);
        prev = current;
    }
    mlist = NULL;
}

static char *get_report_filename(){
    char *fname = getenv("MCHECK_TRACE");
    if (fname == NULL) {
        fname = "mcheck.rpt";
    }
    return fname;
}

void init_report_file(){
    char *fname = get_report_filename();
    FILE *fp = NULL;
    fp = fopen(fname, "w+");
    fclose(fp);
}

static void write_report_file(char *message){
    char *fname = get_report_filename();
    FILE *fp = NULL;
    fp = fopen(fname, "a+");
    fprintf(fp, "%s\n", message);
    fflush(stdout);
    fclose(fp);
}

void mcheck_list_report_leak(mcheck_mem_list *mlist){
    if (mcheck_list_size(mlist) == 0)
    {
        write_report_file("All memory was free, congratulations, well done!");
        return;
    }
    write_report_file("Memory Not Free:");
    write_report_file("-----------------------------");
    write_report_file("\tAddress\t\tSize\t\tCaller");
    mlist = mlist->next;
    while (mlist != NULL)
    {
        mcheck_meminfo mem_info = mlist->mem_info;
        char message[1024] = {0};
        sprintf(message, "\t%p\t%lu\tat\t%s:%d", mem_info.address, mem_info.size, mem_info.caller.file, mem_info.caller.line);
        write_report_file(message);
        mlist = mlist->next;
    }
}