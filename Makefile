windows: IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c memory.c processor.h
	gcc IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c memory.c -o main.exe -std=c99

linux: IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c memory.c processor.h
	gcc IsaSim.c RegisterFile.c StateMachine.c Alu.c control.c instruction.c memory.c -o main.out -std=c99

resread: readres.c
	gcc readres.c -o resread.exe -std=c99

resreadlinux: readres.c
	gcc readres.c -o resread.out -std=c99
	