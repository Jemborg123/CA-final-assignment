
#include <stdlib.h>
#include <stdint.h>

uint32_t Registers[32];

uint32_t ReadRegister(uint8_t r){
    return Registers[r];
}

int WriteRegister(uint8_t r, uint32_t data){
    Registers[r]=data;
    return 0;
}