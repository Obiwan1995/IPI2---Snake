all: play
 
play: main.c game.o snake.o
	gcc -o play main.c game.o snake.o -std=c99 -Wall `sdl-config --libs`

game.o: game.c game.h
	gcc -o game.o -c game.c -std=c99 -Wall

snake.o: snake.c snake.h
	gcc -o snake.o -c snake.c -std=c99 -Wall
 
clean:
	rm -f *.o
	rm -f play