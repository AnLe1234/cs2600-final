CC = gcc
DLLFLAGS=-fPIC --shared

all: tictactoe
obj/tictactoe.o: src/C/tictactoe.c
	$(CC) -c src/C/tictactoe.c -o obj/tictactoe.o
lib/tictactoeDLL.dll: src/C/tictactoe.c
	$(CC) $(DLLFLAGS) -o lib/tictactoeDLL.dll src/C/tictactoe.c

bin/tictactoe:
	$(CC) src/C/tictactoe.c	-o bin/tictactoe
clean:
	del bin/tictactoe.exe obj/tictactoe.o