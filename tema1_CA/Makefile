FLAGS = -g -lm -Wall -Wextra -std=c99
build: tema1.c
	gcc -o tema1 tema1.c $(FLAGS)
clean:
	rm -rf tema1
	rm -f *.out
run:
	valgrind --leak-check=full --show-leak-kinds=all ./tema1>results
	