

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

int32_t extract_b_imm(uint32_t instruction) {
    int32_t imm = 0;
    
    // Extract from instruction and place in immediate bit positions:
    imm |= ((instruction >> 31) & 0x1) << 12;    // inst[31] → imm[12]
    imm |= ((instruction >> 25) & 0x3F) << 5;    // inst[30:25] → imm[10:5]  
    imm |= ((instruction >> 8) & 0xF) << 1;      // inst[11:8] → imm[4:1]
    imm |= ((instruction >> 7) & 0x1) << 11;     // inst[7] → imm[11]
    
    // Sign extend (since B-type uses 13-bit signed immediate)
    if (imm & 0x1000) {  // If bit 12 of immediate is set
        imm |= 0xFFFFE000;  // Sign extend to 32 bits
    }
    return imm;
}

int32_t extract_j_imm(uint32_t instruction) {
    int32_t imm = 0;
    
    // Extract from instruction and place in correct immediate bit positions:
    imm |= ((instruction >> 31) & 0x1) << 20;    // inst[31] → imm[20]
    imm |= ((instruction >> 21) & 0x3FF) << 1;   // inst[30:21] → imm[10:1]  
    imm |= ((instruction >> 20) & 0x1) << 11;    // inst[20] → imm[11]
    imm |= ((instruction >> 12) & 0xFF) << 12;   // inst[19:12] → imm[19:12]
    
    // Sign extend (since J-type uses 21-bit signed immediate)
    if (imm & 0x100000) {  // If bit 20 of immediate is set
        imm |= 0xFFE00000;  // Sign extend to 32 bits
    }
    return imm;
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
    CPU->datapath.Bimm = extract_b_imm(instr);
    CPU->datapath.Jimm = extract_j_imm(instr);
}
