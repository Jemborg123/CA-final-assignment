windows: IsaSim.c RegisterFile.c StateMachine.c
	gcc IsaSim.c RegisterFile.c StateMachine.c -o main.exe -std=c99
linux: IsaSim.c RegisterFile.c StateMachine.c
	gcc IsaSim.c RegisterFile.c StateMachine.c -o main.out -std=c99