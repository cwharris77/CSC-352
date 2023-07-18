arrayz.o: arrayz.c
	gcc -Wall -Werror -std=c11 -c -g arrayz.c -o arrayz.o -lm
basketball: basketball.c	
	gcc -Wall -Werror -std=c11 -g basketball.c -o basketball arrayz.o -lm
clean:
	rm -f arrayz.o basketball
