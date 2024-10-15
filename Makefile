build:
	gcc -g -std=gnu11 -o quadtree main.c functions.c
run:
	./quadtree
clean:
	rm quadtree
valgrind:
	valgrind -s --leak-check=full --show-leak-kinds=all --leak-check=yes --track-origins=yes ./quadtree