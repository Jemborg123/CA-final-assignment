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
    uint32_t instruction;
    uint32_t pc;
    uint32_t read_data1;
    uint32_t read_data2;
    uint32_t alu_result;
    uint32_t mem_read_data;
    uint32_t write_back_data;
    
    // Immediate values
    uint32_t immediate;
    
    // Component connections
    uint32_t alu_a;
    uint32_t alu_b;   
} DataPath;

typedef enum {
    IDLE, IF, ID, EX, MEM, WB, DONE
} States;

typedef struct {
    // Processor state
    unsigned char state;
    
    // Memory and registers
    uint32_t* instrMem; 
    uint32_t* dataMem; 
    uint32_t* registers;
    
    // BUUUUUS
    DataPath datapath;
    
    // Simulation state
    int cycle_count;
    int instructions_executed;
    int running;
} Processor;

#endif