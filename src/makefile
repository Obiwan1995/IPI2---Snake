all: play
 
play: main.c option.o game.o snake.o obstacle.o bonus.o
	gcc -o play main.c option.o game.o snake.o obstacle.o bonus.o -std=c99 -Wall -lm `sdl-config --libs`

option.o: option.c option.h
	gcc -o option.o -c option.c -std=c99 -Wall

game.o: game.c game.h
	gcc -o game.o -c game.c -std=c99 -Wall

snake.o: snake.c snake.h
	gcc -o snake.o -c snake.c -std=c99 -Wall

obstacle.o: obstacle.c obstacle.h
	gcc -o obstacle.o -c obstacle.c -std=c99 -Wall

bonus.o: bonus.c bonus.h
	gcc -o bonus.o -c bonus.c -std=c99 -Wall

test: ../tests/test_main.c snake.o obstacle.o bonus.o
	gcc -o ../tests/test_main ../tests/test_main.c snake.o obstacle.o bonus.o -std=c99 -Wall -lm -l cmocka
 
clean:
	rm -f *.o
	rm -f play
	rm -f ../tests/test_main
