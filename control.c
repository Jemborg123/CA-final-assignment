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
    printf("\nBEFORE SWITCH\n");
    switch (funct3) {
        case beq:
            printf("\n%x BEQ\n",a==b);
            printf("\nBIMM: %d\n",Bimm);
            if(a==b) cpu->datapath.pc = cpu->datapath.pc+(Bimm/4)-1;    
            break;
        case bne: 
            printf("\n%x bne\n",a!=b);
            printf("\nBIMM: %d\n",Bimm);
            if(a!=b) cpu->datapath.pc = cpu->datapath.pc+(Bimm/4)-1;  
            break;
        case blt: 
            printf("\n%x Blt\n",a<b);
            printf("\nBIMM: %d\n",Bimm);
            if(a<b) cpu->datapath.pc = cpu->datapath.pc+(Bimm/4)-1;  
            break;
        case bge: 
            printf("\nBIMM: %d\n",Bimm);
            if(a>=b) cpu->datapath.pc = cpu->datapath.pc+(Bimm/4)-1;  
            break;
        case bltu:
            printf("\nBIMM: %d\n",Bimm);
            if(c<d) cpu->datapath.pc = cpu->datapath.pc+(Bimm/4)-1;   
            break;
        case bgeu: 
            printf("\nBIMM: %d\n",Bimm);
            if(c>=d) cpu->datapath.pc = cpu->datapath.pc+(Bimm/4)-1;  
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
    case JAL:
        int32_t Jimm = cpu->datapath.Jimm;
        reg_write(cpu,cpu->datapath.rd,cpu->datapath.pc*4+4);
        cpu->datapath.pc = cpu->datapath.pc+(Jimm/4)-1;
        cpu->state = IF;
        break;
    case JALR:
        uint16_t Iimm = cpu->datapath.Iimm;
        uint8_t rs1 = cpu->datapath.rs1;
        reg_write(cpu,cpu->datapath.rd,cpu->datapath.pc*4+4);
        cpu->datapath.pc = ((cpu->datapath.rs1+Iimm)/4)-1;
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
        uint32_t val = cpu->datapath.pc*4+cpu->datapath.Uimm;
        reg_write(cpu,cpu->datapath.rd,val);
        cpu->state = IF;
        break;
    default:
        printf("DEFAULT");
        cpu->state = IF;
        break;
    }

}