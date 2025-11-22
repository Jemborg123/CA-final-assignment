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
    
    uint32_t a = reg_read(cpu,rs1);
    uint32_t b = reg_read(cpu,rs2);
    int32_t c = reg_read(cpu,rs2);
    int32_t d = reg_read(cpu,rs2);
    printf("\nBEFORE SWITCH\n");
    switch (funct3) {
        case beq:
            printf("\n%x BEQ\n",a==b);
            if(a==b) cpu->datapath.pc = cpu->datapath.pc+(Bimm<<2);    
            break;
        case bne: 
            printf("\n%x bne\n",a!=b);
            printf("\nBIMM: %d\n",Bimm);
            if(a!=b) cpu->datapath.pc = cpu->datapath.pc+(Bimm<<2);  
            break;
        case blt: 
            printf("\n%x Blt\n",a<b);
            if(a<b) cpu->datapath.pc = cpu->datapath.pc+(Bimm<<2);  
            break;
        case bge: 
            if(a>=b) cpu->datapath.pc = cpu->datapath.pc+(Bimm<<2);  
            break;
        case bltu:
            if(c<d) cpu->datapath.pc = cpu->datapath.pc+(Bimm<<2);   
            break;
        case bgeu: 
            if(c>=d) cpu->datapath.pc = cpu->datapath.pc+(Bimm<<2);  
            break;
        default:
            return;
    }

}

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
    case ILOADTYPE:
        exec_iloadtype(cpu);
        cpu->state = IF;
        break;
    case STYPE:
        printf("STYPE WAS CALLED\n");
        exec_stype(cpu);
        cpu->state = IF;
        break;
    case BTYPE:
        exec_btype(cpu);
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
    case AUIPC:
        cpu->datapath.pc+cpu->datapath.Uimm;
        cpu->state = IF;
        break;
    default:
        printf("DEFAULT");
        cpu->state = IF;
        break;
    }

}