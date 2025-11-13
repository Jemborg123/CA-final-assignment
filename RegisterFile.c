
#include <stdlib.h>
#include <stdint.h>
#include "processor.h"
#include "RegisterFile.h"

static inline uint32_t reg_read(Processor *cpu, uint8_t idx)
{
    if (idx == 0) return 0;
    return cpu->registers[idx];
}

static inline void reg_write(Processor *cpu, uint8_t idx, uint32_t value)
{
    if (idx == 0) return; 
    cpu->registers[idx] = value;
}