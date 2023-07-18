#include <stdio.h>
#include "zstr.h"


int main() {
	char* string = "abcdefghijklmnopqrstuvwxyz";
	//zstr_code c = ZSTR_ERROR;

	zstr z = zstr_create(string);
	//int* c = (int*) z - 2;

	zstr dna = zstr_create("DeoxyribonucleicAcid"); 
	zstr_print_detailed(dna);

	//printf("%d, %d, %s\n",c[0], c[1], z);
	zstr_print_detailed(z);

	zstr y = zstr_create("I go to the shore for the beach"); 
	zstr_print_detailed(y);

	zstr g = zstr_create("sho"); 

	//zstr_append(&y, g); 
	
	int q = zstr_index(y, g);
	printf("index: %d\n", q);

	zstr_print_detailed(y);

	zstr_destroy(z);
	zstr_destroy(dna);
	zstr_destroy(y);
	zstr_destroy(g);


	return 0;
}
