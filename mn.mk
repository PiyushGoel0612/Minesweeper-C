./a.exe : Minesweeper.o client.o
	gcc Minesweeper.o client.o
Minesweeper.o : Minesweeper.c Minesweeper.h
	gcc -c Minesweeper.c
client.o : client.c
	gcc -c client.c