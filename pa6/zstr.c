/*
 * zstr.c
 * Author: Cooper Harris
 * CSC 352
 *
 * This program is the implementation of the custom type zstr which
 * represents a char*. It implements several functions defined by 
 * zstr.h that allow the user to create, destroy, modify and print zstrs.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "zstr.h"

zstr_code code;

int findSize(char* initial_data);

zstr zstr_create(char* initial_data) {
	int sizes[5] = {16, 32, 256, 1024, 2048};

	int dataSize = findSize(initial_data);
	int allocatedLength = 0;
	
	// find the smallest valid length the data will fit into
	for (int i = 0; i < 5; i++) {
		if (dataSize + 9 < sizes[i]) {
			allocatedLength = sizes[i];
			break;
		}
	}

	// allocate the space for the zstr
	int* newZstr = malloc(allocatedLength);
	
	// if the given string was too long or a malloc errror
	if (newZstr == NULL || allocatedLength == 0) {
		code = ZSTR_ERROR;
	}
	
	// put the length of the string and the total space allocated into the zstr
	newZstr[0] = dataSize;
	newZstr[1] = allocatedLength;

	//newZstr += 2;
	char * charZstr = (char*) newZstr + 2*sizeof(int);
	
	// fill the zstring with the given string
	for (int i = 0; initial_data[i] != '\0'; i++) {
		if (initial_data[i+1] == '\0') {
			charZstr[i+1] = '\0';
		} 
		charZstr[i] = initial_data[i];
		
	}

	return charZstr;
}

void zstr_destroy(zstr to_destroy) {
	to_destroy -= sizeof(int)*2;
	
	free(to_destroy);
}

void zstr_append (zstr * base, zstr to_append) {
	int baseSize = findSize(*base);
	int appendSize = findSize(to_append);
	
	// make a string with space for both zstrs and a null pointer
	char temp[baseSize+appendSize+1];

	int i = 0;
	for (; (*base)[i] != '\0'; i++) {
		temp[i] = (*base)[i];
	}
	for (int j = 0; to_append[j] != '\0'; i++, j++) {
		temp[i] = to_append[j];
	}

	temp[i] = '\0';
	
	zstr_destroy(*base);
	*base = zstr_create(temp);
}

void zstr_print_detailed(zstr data) {
	// make an int pointer that points to the real
	// start of the zstring
	int * intptr = (int*) data - 2;
	
	printf("STRLENGTH: %d\n DATASIZE: %d\n   STRING: >%s<\n", intptr[0], intptr[1], data);
}

int zstr_index(zstr base, zstr to_search) {
	int* intBase = (int*) base - 2; 
	int* intSearch = (int*) to_search - 2;
	int index = -1;
	

	int j = 0;
	for (int i = 0; i < intBase[0] && j < intSearch[0]; i++, j++) {
		if (base[i] != to_search[j]) {
			j = -1;
			index = -1;
		} else {
			index = i;
		}
	}
	//printf("%d, %d\n", intBase[0], intSearch[0]);
	if (index != -1) {
		index -= intSearch[0] - 1;
	}

	return index;
}

/*
This function takes a pointer to a null terminated char array and finds the length
of that array
*/
int findSize(char* initial_data) {
	int lenData = 0;

	for (int i = 0; initial_data[i] != '\0'; i++) {
		lenData++;
	}
	
	return lenData;
}
