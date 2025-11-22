#ifndef REGISTERFILE_H
#include "processor.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int32_t reg_read(Processor *cpu, uint8_t idx);

void reg_write(Processor *cpu, uint8_t idx, int32_t value);

void dump_registers(Processor *cpu,char* filename);
void dump_registers_humanReadable(Processor *cpu);
void debug_register(Processor *cpu, uint8_t idx);
#endif