
#include "RegisterFile.h"
#include "IsaSim.h"
#include "instruction.h"
#include "control.h"

int StateMachine(Processor *CPU){
    switch (CPU->state)
    {
    case IDLE:
        CPU->state = IF;
        break;
    case IF:
        int32_t instr = fetchInstruction(CPU);
        CPU->state = ID;
        break;
    case ID:
        decodeInstruction(CPU,instr);
        CPU->state = EX;
        break;
    case EX:
        debug_register(CPU,10);
        debug_register(CPU,11);
        step(CPU);
        break;
    case MEM:
        /* code */
        break;
    case WB:
        /* code */
        break;
    case DONE:
        printf("State machine is done");
        CPU->running = 0;
        dump_registers(CPU);
        break;
    
    default:
        break;
    }
    return 0;
}