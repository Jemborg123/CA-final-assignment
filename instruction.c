

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "processor.h"
#include "instruction.h"

int32_t fetchInstruction(Processor *CPU){
    printf("FETCH INSTRUCTION%d\n",CPU->datapath.pc);
    int32_t instr = CPU->instrMem[CPU->datapath.pc];
    printf("instruction: %x\n",instr);
    CPU->datapath.pc=CPU->datapath.pc+1;
    
    return instr;
}


