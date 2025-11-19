#ifndef ALU_H
#define ALU_H

#include <stdint.h>
#include "processor.h"
#include "RegisterFile.h"


typedef enum {
    ALU_ADD,
    ALU_SUB,
    ALU_AND,
    ALU_OR,
    ALU_XOR
} AluControl;

int32_t alu_execute(int32_t a, int32_t b, AluControl ctrl);
void exec_rtype(Processor *cpu);
void exec_itype(Processor *cpu);

#endif