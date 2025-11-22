#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "processor.h"
#include "RegisterFile.h"
#include "StateMachine.h"

#define NO_ERR 0;

char* generateNameFromInput(char* in){
  const char *ext = strrchr(in, '.');
  size_t base_len = ext-in;
  char* out = malloc(strlen(in)+strlen("Answer")+strlen(".res")+1);
  memcpy(out, in, base_len);
  out[base_len] = '\0';

  strcat(out, "Answer");
  strcat(out, ".res");
  return out;
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
      fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
      exit(1);
  }

  char* resultFilename = generateNameFromInput(argv[1]);

  FILE* fptr;
  int32_t instr, opcode, rd, rs1, rs2, funct3, funct7, Iimm, Simm, Uimm;
  Processor CPU;
  CPU.datapath.pc = 0;
  CPU.state = IDLE;
  for(int i =0; i<MEMORY_SIZE; i++){
    CPU.instrMem[i]=0;
  }
  for(int i = 0; i<NUM_REGISTERS; i++){
    CPU.registers[i]=0;
  }
  uint8_t n=0;
  fptr = fopen(argv[1], "rb");

  fseek(fptr, 0, SEEK_END);
  uint32_t sz = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);
  printf("file length:%d\n",sz);

  for(int i = 0 ; i<sz/4;i++){
    fread(&instr, sizeof(int), 1, fptr);

    opcode = instr & 0x7f; 
    rd = (instr >> 7) & 0x01f;
     Uimm = ((instr >> 12)<<12);

    printf("line: %x,\t Opcode: %x,\t UIMM: %x,\t rd: %x \n", instr,opcode,Uimm,rd);

    CPU.instrMem[n]=instr;
    n=n+1;
  }

  CPU.running = 1;
  CPU.cycle_count = 0;
  while (CPU.running&&CPU.cycle_count<1000){
    CPU.cycle_count++;
    StateMachine(&CPU,resultFilename);
  }

  fclose(fptr);
  return NO_ERR;
}