all: game

game:
	gcc -o game ./src/*.c -lncursesw

clean:
	rm game
