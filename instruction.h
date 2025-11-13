
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
uint32_t fetchInstruction(Processor *CPU, uint32_t pc);
uint32_t DecodeOpcode(uint32_t opcode);

#endif