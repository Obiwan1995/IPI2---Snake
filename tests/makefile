all: test_snake
 
test_snake: test_snake.c snake.o obstacle.o
	gcc -o test_snake test_snake.c snake.o obstacle.o -std=c99 -Wall `pkg-config --libs cmocka`

snake.o: ../src/snake.c ../src/snake.h
	gcc -o snake.o -c ../src/snake.c -std=c99 -Wall

obstacle.o: ../src/obstacle.c ../src/obstacle.h
	gcc -o obstacle.o -c ../src/obstacle.c -std=c99 -Wall
 
clean:
	rm -f *.o
	rm -f test_snake