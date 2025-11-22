#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "processor.h"
#include "RegisterFile.h"


typedef enum {
    lb,
    lh,
    lw,
    lbu,
    lhu
} ILOADcontrol;

typedef enum {
    sb,
    sh,
    sw
} Scontrol;

void exec_iloadtype(Processor *cpu);
void exec_stype (Processor *cpu);

#endif