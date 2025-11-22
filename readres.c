#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char** argv)
{
  if (argc != 2)
  {
      fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
      exit(1);
  }

  FILE* fptr;
  fptr = fopen(argv[1], "rb"); //open read binary file
  uint32_t reg;
  fseek(fptr, 0, SEEK_END);
  uint32_t sz = ftell(fptr);
  fseek(fptr, 0, SEEK_SET);
  for(int i = 0 ; i<sz/4;i++){ //load program into instruction memory
    fread(&reg, sizeof(int), 1, fptr); //read instructions in bin file
    printf("line: %x\n", reg); //print instruction & opcode
  }


  fclose(fptr);
  return 0;
}

