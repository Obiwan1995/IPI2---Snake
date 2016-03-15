all: play
 
play: main.c game.o snake.o obstacle.o
	gcc -o play main.c game.o snake.o obstacle.o -std=c99 -Wall `sdl-config --libs`

game.o: game.c game.h obstacle.o
	gcc -o game.o -c game.c obstacle.o -std=c99 -Wall

snake.o: snake.c snake.h obstacle.o
	gcc -o snake.o -c snake.c -std=c99 -Wall

obstacle.o: obstacle.c obstacle.h
	gcc -o obstacle.o -c obstacle.c -std=c99 -Wall
 
clean:
	rm -f *.o
	rm -f play