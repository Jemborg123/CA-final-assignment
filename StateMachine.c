#include "IsaSim.h"
#include "instruction.h"
#include "control.h"
int StateMachine(Processor *CPU){
    switch (CPU->state)
    {
    case IDLE:
        /* code */
        break;
    case IF:
        uint32_t instr = fetchInstruction(CPU,CPU->datapath.pc);
        CPU->state = ID_EX;
        break;
    case ID_EX:
        /* code */
        break;
    case MEM:
        /* code */
        break;
    case WB:
        /* code */
        break;
    case DONE:
        /* code */
        break;
    
    default:
        break;
    }
    return 0;
}