#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "processor.h"
#include "RegisterFile.h"

int32_t reg_read(Processor *cpu, uint8_t idx)
{
    if (idx == 0) return 0;
    return cpu->registers[idx];
}

void reg_write(Processor *cpu, uint8_t idx, int32_t value)
{
    if (idx == 0) return; 
    cpu->registers[idx] = value;
}

void dump_registers_humanReadable(Processor *cpu){
    FILE *fptr;
    fptr = fopen("readableres", "w");
    for(int i =0; i<NUM_REGISTERS; i++){
        fprintf(fptr, "x%d: %x\n", i,cpu->registers[i]);
    }
    fclose(fptr); 
}

void dump_registers(Processor *cpu,char* filename){
    FILE *fptr;
    fptr = fopen(filename, "wb");

    fwrite(cpu->registers, sizeof(cpu->registers[0]), NUM_REGISTERS, fptr);
    fclose(fptr); 
}

void debug_register(Processor *cpu, uint8_t idx){
    printf("In x%d: %x\n",idx,cpu->registers[idx]);
}
