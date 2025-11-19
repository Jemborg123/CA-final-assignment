#include "processor.h"
#include "RegisterFile.h"
#include "Alu.h"


void step(Processor *cpu) {      
    switch (cpu->datapath.opcode)
    {
    case RTYPE:
        printf("RTYPE");
        exec_rtype(cpu);
        cpu->state = IF;
        break;
    case ITYPE:
        printf("ITYPE");
        exec_itype(cpu);
        cpu->state = IF;
        break;
    case ECALL:
        printf("ecall");
        cpu->state = DONE;
        break;
    case LUI:
        printf("LUI");
        reg_write(cpu,cpu->datapath.rd,cpu->datapath.Uimm);
        cpu->state = IF;
        break;
    default:
        printf("DEFAULT");
        cpu->state = IF;
        break;
    }

}