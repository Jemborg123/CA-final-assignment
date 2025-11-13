//To compile (linux/mac): gcc IsaSim.c -o main.out -std=c99
//To run (linux/mac): ./main.out <file>.bin

//To compile (win): gcc IsaSim.c -o main.exe -std=c99 
//To run (win): ./main.exe <file>.bin

    // opcode = instr & 0x7f; 
    // rd = (instr >> 7) & 0x01f;
    // rs1 = (instr >> 15) & 0x01f;
    // rs2 = (instr >> 20) & 0x01f;
    // funct3 = (instr >> 12) & 0x007;
    // funct7 = (instr >> 25);
    // Iimm = (instr >> 20);
    // Simm = ((instr >> 6) & 0x01f ) + ((instr >> 20) << 5); 
    // Uimm = (instr >> 12);

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "processor.h"
#include "RegisterFile.h"
#include "StateMachine.h"

#define NO_ERR 0;

int main(int argc, char** argv)
{
  if (argc != 2)
  {
      fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
      exit(1);
  }

  FILE* fptr;
  uint32_t instr, opcode, rd, rs1, rs2, funct3, funct7, Iimm, Simm, Uimm;
  Processor CPU;
  CPU.instrMem = (uint32_t*)malloc(sizeof(uint32_t)*MEMORY_SIZE);
  CPU.dataMem = (uint32_t*)malloc(sizeof(uint32_t)*MEMORY_SIZE);
  CPU.registers = (uint32_t*)malloc(sizeof(uint32_t)*NUM_REGISTERS);
  uint8_t n=0;
  fptr = fopen(argv[1], "rb"); //open read binary file

  for(;;){ //load program into instruction memory
    fread(&instr, sizeof(int), 1, fptr); //read instructions in bin file
    opcode = instr & 0x7f; //temp opcode debug help
    printf("line: %x,\t Opcode: %x\n", instr,opcode); //print instruction & opcode

    CPU.instrMem[n]=instr; //save instruction in instructionmemory
    ++n;

    if(opcode==0x73){ //0x73: ecall
        break;
    }
  }
  free(CPU.instrMem);
  free(CPU.dataMem);
  free(CPU.registers);
  fclose(fptr);
  return NO_ERR;
}

