#include "mcheck.h"

int main(void){
    mcheck_initialize();
    void *p1 = malloc(10);
    void *p2 = malloc(20);
    free(p1);
    //free(p2);
    void *p3 = malloc(30);
    free(p3);
    test();
    void *p4 = calloc(1, 64);
    void *p5 = malloc(32);
    void *p6 = realloc(p5, 128);
    mcheck_terminate();
    return 0;
}