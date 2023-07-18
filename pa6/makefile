zstr.o: zstr.c
	gcc -Wall -Werror -std=c11 -c -g zstr.c -o zstr.o
test: test_zstr.c zstr.o
	gcc -Wall -Werror -std=c11 -g test_zstr.c -o test zstr.o
clean: 
	rm -f zstr.o
clean_test: 
	rm -f test

