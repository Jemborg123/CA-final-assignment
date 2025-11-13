
#include <stdint.h>
#include "instruction.h"
#include "processor.h"



uint32_t fetchInstruction(Processor *CPU, uint32_t pc){
    return CPU->instrMem[pc++];
}


