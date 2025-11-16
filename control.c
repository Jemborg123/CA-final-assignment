#include "processor.h"
#include "RegisterFile.h"
#include "Alu.h"

enum types{
    ITYPE = 0x13,
    RTYPE = 0x33,
    ECALL = 0x73,
    LUI = 0x37
};
void step(Processor *cpu, int32_t instr) {

    uint8_t opcode = instr & 0x7f;
    int32_t rd = (instr >> 7) & 0x01f;
      
    switch (opcode)
    {
    case RTYPE:
        printf("RTYPE");
        exec_rtype(cpu, instr);
        cpu->state = IF;
        break;
    case ITYPE:
        printf("ITYPE");
        exec_itype(cpu, instr);
        cpu->state = IF;
        break;
    case ECALL:
        printf("ecall");
        cpu->state = DONE;
        break;
    case LUI:
        printf("LUI");
        int32_t Uimm = ((instr >> 12)<<12);
        reg_write(cpu,rd,Uimm);
        cpu->state = IF;
        break;
    default:
        printf("DEFAULT");
        cpu->state = IF;
        break;
    }

}