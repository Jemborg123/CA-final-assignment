windows: IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h memory.c
	gcc IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h memory.c  -o main.exe -std=c99
linux: IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h memory.c
	gcc IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c processor.h memory.c  -o main.out -std=c99

resread: readres.c
	gcc readres.c -o readres.exe -std=c99