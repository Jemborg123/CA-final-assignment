
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "processor.h"

int32_t fetchInstruction(Processor *CPU);

#endif