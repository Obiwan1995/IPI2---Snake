all: play
 
play: main.c option.o game.o snake.o obstacle.o
	gcc -o play main.c option.o game.o snake.o obstacle.o -std=c99 -Wall `sdl-config --libs`

option.o: option.c option.h
	gcc -o option.o -c option.c -std=c99 -Wall

game.o: game.c game.h
	gcc -o game.o -c game.c -std=c99 -Wall

snake.o: snake.c snake.h
	gcc -o snake.o -c snake.c -std=c99 -Wall

obstacle.o: obstacle.c obstacle.h
	gcc -o obstacle.o -c obstacle.c -std=c99 -Wall

test: ../tests/test_snake.c snake.o obstacle.o
	gcc -o ../tests/test_snake ../tests/test_snake.c snake.o obstacle.o -std=c99 -Wall -l cmocka
 
clean:
	rm -f *.o
	rm -f play
	rm -f ../tests/test_snake
