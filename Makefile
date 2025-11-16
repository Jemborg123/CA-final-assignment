windows: IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h 
	gcc IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h  -o main.exe -std=c99
linux: IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h 
	gcc IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h  -o main.out -std=c99