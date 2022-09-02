FLAGS = -g -lm -Wall -Wextra -std=c99
build: quadtree.c
	gcc -o quadtree quadtree.c $(FLAGS)
clean:
	rm -rf main
	rm -f *.out
run:
	valgrind --leak-check=full --show-leak-kinds=all ./quadtree -c 0 test1.ppm output.ppm 2>results