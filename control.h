#ifndef CONTROL_H
#define CONTROL_H
void step(Processor *cpu);

typedef enum {
    beq = 0x0,
    bne = 0x1,
    blt = 0x4,
    bge = 0x5,
    bltu = 0x6,
    bgeu = 0x7
} Bcontrol;

#endif
