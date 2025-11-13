#include <stdlib.h>
#include <stdint.h>

int initInstrMem(){
    int *imemptr = (uint32_t*)malloc(256*sizeof(uint32_t));//256 ints
    return *imemptr;
}

int initDataMem(){
    int *dmemptr = (uint32_t*)malloc(256*sizeof(uint32_t));//256 ints
    return *dmemptr;
}