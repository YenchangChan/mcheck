#include <stdio.h>
#include <stdlib.h>
#include "mcheck.h"

void test(){
    void *p1 = malloc(10);
    void *p2 = malloc(20);
    free(p1);
    void *p3 = malloc(30);
    free(p3);
    void *p4 = calloc(1, 64);
    void *p5 = malloc(32);
    void *p6 = realloc(p5, 128);
}