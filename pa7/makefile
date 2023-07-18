gcc_args = gcc -Wall -Werror -std=c11

game: game.c tq.o
	$(gcc_args) game.c -o game tq.o
tq.o: tq.c
	$(gcc_args) -c tq.c -o tq.o
clean:
	rm -f tq.o game

	
