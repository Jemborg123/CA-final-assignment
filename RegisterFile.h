#ifndef REGISTERFILE_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static inline uint32_t reg_read(Processor *cpu, uint8_t idx);

static inline void reg_write(Processor *cpu, uint8_t idx, uint32_t value);

#endif