#ifndef ALU_H
#define ALU_H

#include <stdint.h>

typedef enum {
    ALU_ADD,
    ALU_SUB,
    ALU_AND,
    ALU_OR,
    ALU_XOR
} AluControl;

uint32_t alu_execute(uint32_t a, uint32_t b, AluControl ctrl);

#endif