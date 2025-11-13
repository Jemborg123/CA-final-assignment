#include "processor.h"
#include "RegisterFile.h"
enum types{
    ITYPE = 0x13,
    RTYPE = 0x33,
    ECALL = 0x73,
    LUI = 0x37
};
void step(Processor *cpu) {

    uint32_t instr = cpu->instrMem[cpu->datapath.pc];
    uint8_t opcode = instr & 0x7f;
    uint8_t rd = (instr >> 7) & 0x01f;
    uint32_t Uimm = (instr >> 12);
      
    switch (opcode)
    {
    case RTYPE:
        exec_rtype(cpu, instr);
        break;
    case ITYPE:
        break;
    case ECALL:
        cpu->running = 0;
        break;
    case LUI:
        reg_write(cpu,rd,Uimm<<12);
        break;
    default:
        break;
    }

}