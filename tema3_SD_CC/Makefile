FLAGS = -g -lm -Wall -Wextra -std=c99
build: tema3.c
	gcc -o tema3 tema3.c $(FLAGS)
clean:
	rm -rf tema3
	rm -f *.out
run:
	valgrind --leak-check=full --show-leak-kinds=all ./tema3>results
