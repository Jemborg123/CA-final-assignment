#include "Alu.h"
#include "RegisterFile.h"
#include "processor.h"

uint32_t alu_execute(uint32_t a, uint32_t b, AluControl ctrl)
{
    switch (ctrl) {
        case ALU_ADD: return a + b;
        case ALU_SUB: return a - b;
        case ALU_AND: return a & b;
        case ALU_OR:  return a | b;
        case ALU_XOR: return a ^ b;
        default:      return 0;
    }
}

void exec_rtype(Processor *cpu, uint32_t instr)
{
    uint8_t rd     = (instr >> 7)  & 0x1f;
    uint8_t funct3 = (instr >> 12) & 0x07;
    uint8_t rs1    = (instr >> 15) & 0x1f;
    uint8_t rs2    = (instr >> 20) & 0x1f;
    uint8_t funct7 = (instr >> 25);

    uint32_t a = reg_read(cpu, rs1);
    uint32_t b = reg_read(cpu, rs2);
    AluControl alu_ctrl;

    switch (funct3) {
        case 0x0:
            if (funct7 == 0x20)
                alu_ctrl = ALU_SUB;
            else
                alu_ctrl = ALU_ADD;
            break;
        case 0x4: alu_ctrl = ALU_XOR; break;
        case 0x6: alu_ctrl = ALU_OR;  break;
        case 0x7: alu_ctrl = ALU_AND; break;
        default:
            return;
    }

    uint32_t result = alu_execute(a, b, alu_ctrl);
    reg_write(cpu, rd, result);
}



