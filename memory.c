#include <stdlib.h>
#include <stdint.h>
#include "processor.h"
#include "RegisterFile.h"
#include "memory.h"


void storeInMem(Processor *cpu, uint32_t memAdrr, uint8_t rs2,Scontrol ctrl){

switch (ctrl)
    {
    case sb:
        uint32_t valueToStore = reg_read(cpu,rs2);
        printf("%x is what is stored in rs2",valueToStore);
        cpu->instrMem[memAdrr>>2] = valueToStore;
        printf("\nvalue: %x expected to be at %x\n",cpu->instrMem[memAdrr>>2],&cpu->instrMem[memAdrr>>2]);
        break;
    case sh:
        cpu->instrMem[memAdrr>>2] = reg_read(cpu, rs2);
        break;
    case sw:
        cpu->instrMem[memAdrr>>2] = reg_read(cpu, rs2);
        break;
    default:
        printf("STORE COULDNT FIND TYPE\n");
        break;
    }
    printf("STOREINMEM FINISHED\n");
}

int32_t loadFromMem(Processor *cpu, uint32_t memAdrr, ILOADcontrol ctrl){
    
uint8_t* byte_mem = (uint8_t*)&cpu->instrMem;
    switch (ctrl)
    {
    case lb:
        printf("\nloading value from %x\n",byte_mem[memAdrr]);
        return (char)byte_mem[memAdrr];
    case lh:
        return (short)byte_mem[memAdrr];
    case lw:
        return (long)byte_mem[memAdrr];
    case lbu:
        return (char)byte_mem[memAdrr];
    case lhu:
        return (short)byte_mem[memAdrr];
    
    default:
        break;
    }
    return 0;
}
static inline int32_t signext_12(int32_t x)
{
    return (int32_t)(x << 20) >> 20;
}

void exec_iloadtype(Processor *cpu)
{
    uint8_t rd     = cpu->datapath.rd;
    uint8_t funct3 = cpu->datapath.funct3;
    uint8_t rs1    = cpu->datapath.rs1;
    int32_t imm    = signext_12(cpu->datapath.Iimm);

    uint32_t memAdrr = reg_read(cpu, rs1)+imm;
    ILOADcontrol ctrl;

    switch (funct3) {
        case 0x0: ctrl = lb; break;
        case 0x1: ctrl = lh; break; 
        case 0x2: ctrl = lw;  break;
        case 0x4: ctrl = lbu; break;
        case 0x5: ctrl = lhu; break;
        default:
            printf("Unsupported I-load-type funct3=0x%x\n", funct3);
            return;
    }
    int32_t result = loadFromMem(cpu,memAdrr,ctrl);
    reg_write(cpu,rd,result);
}

void exec_stype (Processor *cpu){
    uint8_t rd     = cpu->datapath.rd;
    uint8_t funct3 = cpu->datapath.funct3;
    uint8_t rs1    = cpu->datapath.rs1;
    uint8_t rs2    = cpu->datapath.rs2;
    int32_t imm    = signext_12(cpu->datapath.Iimm);

    uint32_t memAdrr = reg_read(cpu, rs1)+imm;
    Scontrol ctrl;
    switch (funct3) {
        case 0x0: ctrl = sb; break;
        case 0x1: ctrl = sh; break; 
        case 0x2: ctrl = sw;  break;
        default:
            printf("Unsupported S-type funct3=0x%x\n", funct3);
            return;
    }
    printf("EXEC STYPE FINISHED RUNNING\n");
    storeInMem(cpu,memAdrr,rs2,ctrl);
}