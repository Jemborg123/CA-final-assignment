#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdint.h>

#define NUM_REGISTERS 32
#define MEMORY_SIZE 256

typedef struct{
    // Control wires
    uint8_t branch;
    uint8_t memRead;
    uint8_t memToReg;
    uint8_t aluOP;
    uint8_t memWrite;
    uint8_t aluSRC;
    uint8_t regWrite;
    
    // Data wires
    int32_t instruction;
    uint32_t pc;
    int32_t read_data1;
    int32_t read_data2;
    int32_t alu_result;
    int32_t mem_read_data;
    int32_t write_back_data;
    
    // Immediate values
    int32_t immediate;
    
    // Component connections
    int32_t alu_a;
    int32_t alu_b;   

    // Instruction parts
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    uint8_t funct3;
    uint8_t funct7;
    uint16_t Iimm;
    uint32_t Simm;
    uint32_t Uimm;

} DataPath;

typedef enum {
    IDLE, IF, ID, EX, MEM, WB, DONE
} States;

typedef enum {
    ITYPE = 0x13,
    RTYPE = 0x33,
    ECALL = 0x73,
    LUI = 0x37,
    DEFAULT = 0x0
} InstrTypes;

typedef struct {
    // Processor state
    unsigned char state;
    
    // Memory and registers
    int32_t instrMem[MEMORY_SIZE]; 
    int32_t dataMem[MEMORY_SIZE]; 
    int32_t registers[NUM_REGISTERS];
    
    // BUUUUUS
    DataPath datapath;
    
    // Simulation state
    int cycle_count;
    int instructions_executed;
    int running;
} Processor;

#endif