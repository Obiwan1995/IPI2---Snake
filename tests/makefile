all: test_snake
 
test_snake: test_snake.c snake.o
	gcc -o test_snake test_snake.c snake.o -std=c99 -Wall `pkg-config --libs cmocka`

snake.o: ../src/snake.c ../src/snake.h
	gcc -o snake.o -c ../src/snake.c -std=c99 -Wall
 
clean:
	rm -f *.o
	rm -f test_snake