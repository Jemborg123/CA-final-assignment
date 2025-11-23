#include "processor.h"
#include "RegisterFile.h"
#include "Alu.h"

int32_t alu_execute(int32_t a, int32_t b, AluControl ctrl)
{
    switch (ctrl) {
        case ALU_ADD: return a + b;
        case ALU_SUB: return a - b;
        case ALU_AND: return a & b;
        case ALU_OR:  return a | b;
        case ALU_XOR: return a ^ b;
        case ALU_SLL: return a << (b & 0x1F);
        case ALU_SRL: return (uint32_t)a >> (b & 0x1F);
        case ALU_SRA: return a >> (b & 0x1F);
        case ALU_SLT: return (a < b) ? 1 : 0;
        case ALU_SLTU: return ((uint32_t)a < (uint32_t)b) ? 1 : 0;
        default:      return 0;
    }
}

void exec_rtype(Processor *cpu)
{
    uint8_t rd     = cpu->datapath.rd;
    uint8_t funct3 = cpu->datapath.funct3;
    uint8_t rs1    = cpu->datapath.rs1;
    uint8_t rs2    = cpu->datapath.rs2;
    uint8_t funct7 = cpu->datapath.funct7;

    int32_t a = reg_read(cpu, rs1);
    int32_t b = reg_read(cpu, rs2);
    AluControl alu_ctrl;

    switch (funct3) {
        case 0x0:
            if (funct7 == 0x20)
                alu_ctrl = ALU_SUB;
            else
                alu_ctrl = ALU_ADD;
            break;
        case 0x1: alu_ctrl = ALU_SLL; break;
        case 0x2: alu_ctrl = ALU_SLT; break;
        case 0x3: alu_ctrl = ALU_SLTU; break;
        case 0x4: alu_ctrl = ALU_XOR; break;
        case 0x5:
            if (funct7 == 0x20)
                alu_ctrl = ALU_SRA;
            else 
                alu_ctrl = ALU_SRL;
            break;
        case 0x6: alu_ctrl = ALU_OR;  break;
        case 0x7: alu_ctrl = ALU_AND; break;
        default:
            return;
    }

    int32_t result = alu_execute(a, b, alu_ctrl);
    reg_write(cpu, rd, result);
}

static inline int32_t signext_12(int32_t x)
{
    return (int32_t)(x << 20) >> 20;
}

void exec_itype(Processor *cpu)
{
    uint8_t rd     = cpu->datapath.rd;
    uint8_t funct3 = cpu->datapath.funct3;
    uint8_t rs1    = cpu->datapath.rs1;
    uint8_t funct7 = cpu->datapath.funct7;
    int32_t imm    = signext_12(cpu->datapath.Iimm);

    int32_t a = reg_read(cpu, rs1);
    int32_t b = (int32_t)imm;
    AluControl alu_ctrl;

    switch (funct3) {
        case 0x0: alu_ctrl = ALU_ADD; break;
        case 0x1: alu_ctrl = ALU_SLL; break;
        case 0x2: alu_ctrl = ALU_SLT; break;
        case 0x3: alu_ctrl = ALU_SLTU; break;
        case 0x4: alu_ctrl = ALU_XOR; break;
        case 0x5:
            if (funct7 == 0x20)
                alu_ctrl = ALU_SRA;
            else 
                alu_ctrl = ALU_SRL;
            break; 
        case 0x6: alu_ctrl = ALU_OR;  break;
        case 0x7: alu_ctrl = ALU_AND; break;
        default:
            printf("Unsupported I-type funct3=0x%x\n", funct3);
            return;
    }

    int32_t result = alu_execute(a, b, alu_ctrl);
    reg_write(cpu, rd, result);
}

