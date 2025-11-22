

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

void decodeInstruction(Processor *CPU, uint32_t instr){
    CPU->datapath.opcode = instr & 0x7f; 
    CPU->datapath.rd = (instr >> 7) & 0x01f;
    CPU->datapath.rs1 = (instr >> 15) & 0x01f;
    CPU->datapath.rs2 = (instr >> 20) & 0x01f;
    CPU->datapath.funct3 = (instr >> 12) & 0x007;
    CPU->datapath.funct7 = (instr >> 25);
    CPU->datapath.Iimm = (instr >> 20);
    CPU->datapath.Simm = ((instr >> 6) & 0x01f ) + ((instr >> 20) << 5); 
    CPU->datapath.Uimm = (instr >> 12)<<12;
    CPU->datapath.Bimm = ((0| (((instr >> 31) & 0x1) << 12) | (((instr >> 25) & 0x3F) << 5) | (((instr >> 8) & 0xF) << 1) | (((instr >> 7) & 0x1) << 11))<<19)>>19;
}
