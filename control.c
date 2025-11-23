#include "processor.h"
#include "RegisterFile.h"
#include "Alu.h"
#include "memory.h"
#include "control.h"

void exec_btype(Processor *cpu){
    uint8_t funct3 = cpu->datapath.funct3;
    uint8_t rs1    = cpu->datapath.rs1;
    uint8_t rs2    = cpu->datapath.rs2;
    int16_t Bimm  = cpu->datapath.Bimm;
    
    int32_t a = reg_read(cpu,rs1);
    int32_t b = reg_read(cpu,rs2);
    uint32_t c = reg_read(cpu,rs2);
    uint32_t d = reg_read(cpu,rs2);

    char shouldBranch = 0x0;
    switch (funct3) {
        case beq:
            shouldBranch = (a==b);    
            break;
        case bne: 
            shouldBranch = (a!=b);  
            break;
        case blt: 
            shouldBranch = (a<b) ;  
            break;
        case bge: 
            shouldBranch = (a>=b) ;  
            break;
        case bltu:
            shouldBranch = (c<d) ;   
            break;
        case bgeu: 
            shouldBranch = (c>=d) ;  
            break;
        default:
            return;
    }
    if(shouldBranch) {
        cpu->datapath.pc = cpu->datapath.pc+(Bimm/4);
        cpu->datapath.pcmux = 1;
    }
}

void step(Processor *cpu) {      
    switch (cpu->datapath.opcode)
    {
    case RTYPE:
        exec_rtype(cpu);
        cpu->state = IF;
        break;
    case ITYPE:
        exec_itype(cpu);
        cpu->state = IF;
        break;
    case ILOADTYPE:
        exec_iloadtype(cpu);
        cpu->state = IF;
        break;
    case STYPE:
        exec_stype(cpu);
        cpu->state = IF;
        break;
    case BTYPE:
        exec_btype(cpu);
        cpu->state = IF;
        break;
    case JAL:
        reg_write(cpu,cpu->datapath.rd,(cpu->datapath.pc*4)+4);
        cpu->datapath.pc = cpu->datapath.pc+(cpu->datapath.Jimm/4);
        cpu->datapath.pcmux = 1;
        cpu->state = IF;
        break;
    case JALR:
        reg_write(cpu,cpu->datapath.rd,(cpu->datapath.pc*4)+4);
        cpu->datapath.pc = (reg_read(cpu,cpu->datapath.rs1)+cpu->datapath.Iimm)/4;
        cpu->datapath.pcmux = 1;
        cpu->state = IF;
        break;
        
    case ECALL:
        cpu->state = DONE;
        break;
    case LUI:
        reg_write(cpu,cpu->datapath.rd,cpu->datapath.Uimm);
        cpu->state = IF;
        break;
    case AUIPC:
        reg_write(cpu,cpu->datapath.rd,(cpu->datapath.pc*4)+cpu->datapath.Uimm);
        cpu->state = IF;
        break;
    default:
        printf("DEFAULT");
        cpu->state = IF;
        break;
    }

}
