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
} DataPath;

typedef enum {
    IDLE, IF, ID_EX, MEM, WB, DONE
} States;

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