/*
 * scut.c
 * Author: Cooper Harris
 * Course: CSC 352
 *
 * This program is a simplified version of the cut command. 
 * input should be formatted like: scut options values
 * where options may be -l, -w, or -c. Values must be 
 * one or more numbers separated by commas or dashes 
 * like 1 or 3,4 or 8-78,79
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void letter(char buffer[], char commands[]);
void whitespace(char buffer[], char commands[]);
void comma(char buffer[], char commands[]);
int  checkInput(char input[], int inputLen);
int  convertToInt(char commands[], int commandsIndex);
int  isASpace(char c);

int main(int argc, char * argv[]){
	/* Error checking to make sure the correct number of arguments
	 * are given and that the input is correctly formatted.
	 */
	if (argc != 3){
		fprintf(stderr, "expected 2 command line arguments.\n");
		return 1;
	}

	int returnCode = checkInput(argv[2], strlen(argv[2]));
	if (returnCode != 0) {
		return 1;
	}
	char buffer[100];
	// choose a function bassed on the flag given, if it is not valid, exit
	if (strcmp(argv[1], "-l") == 0) {
		letter(buffer, argv[2]);
	} else if (strcmp(argv[1], "-w") == 0) {
		whitespace(buffer, argv[2]);
	} else if (strcmp(argv[1], "-c") == 0) {
		comma(buffer, argv[2]);
	} else {
		fprintf(stderr, "Invalid delimiter type.\n");
		return 1;
	}
	return 0;
}

/*
 * This function takes an array of chars and an index to begin at
 * and returns either a one or two digit int value of the char at the index given
 * It determines if the int is one or two digits by checking if the value at the 
 * next index is a digit based on its ascii code.
 */
int convertToInt(char commands[], int commandsIndex) {
	int num;
	// if the ascii code is greater than 47 it is a digit because error checking 
	// already made sure there is only digits, commas and dashes
	if (commands[commandsIndex+1] > 47 && (commandsIndex+1) <= strlen(commands)) {
		//subtract 48 to turn ascii number into a digit 0-9
		num = (10 * (commands[commandsIndex] - 48)) + commands[commandsIndex+1] - 48;
	} else {
		num = commands[commandsIndex] - 48;
	}

	return num;
}	

/*
 * This function splits the given input by letter. It takes an array that will hold
 * up to 100 chars read in and an array containing the column numbers to print.
 */
void letter(char buffer[], char commands[]) {
	int commandsIndex = 0;
	int column = 1;
	int upperBound;
	int inRange = 0;
	int num;

	while (fgets(buffer, 100, stdin) != NULL) {
		for (int i=0; i < strlen(buffer); i++) {
			// if this char is a digit
			if (commands[commandsIndex] > 47) {
				num = convertToInt(commands, commandsIndex);
			}
			// all columns in the given range should be printed
			// so the boolean inRange will be true until it is 
			// greater than the number after the -
			if (commands[commandsIndex] == '-') {
				inRange = 1;
				upperBound = convertToInt(commands, commandsIndex+1);
				commandsIndex++;
			} 
			// checking to see if its still in range
			if (i >= upperBound){
				inRange = 0;
			}
			// this is a separator char that we don't care
			// about so advance to the next one
			if (commands[commandsIndex] == ',') {
				commandsIndex++;
				num = convertToInt(commands, commandsIndex);
			} 
			// if the column number matches the value in the commands array
			// or if we are within a range print the char in the column
			if (column == num || inRange == 1) {
				printf("%c ", buffer[i]);
				commandsIndex++;
				// if it is a two digit number advance the index to the next
				// value that isnt part of this number
				if (num > 9) {
					commandsIndex++;
				}
			} 
			if (buffer[i] == '\n') {
				printf("\n");
				// these values need to be reset for each new line
				column = 0;
				commandsIndex = 0;
				inRange = 0;
			} 
			column += 1;
		}
	}
}

/*
 * This function returns 1 if a whitespace char is found
 */
int isASpace(char c) {
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r') {
		return 1;
	} else {
		return 0;
	}
}


/*
 * This function splits the given input by whitespace. It takes an array that will hold
 * up to 100 chars read in and an array containing the column numbers to print.
 */
void whitespace(char buffer[], char commands[]) {
	int commandsIndex = 0;
	int column = 1;
	int upperBound;
	int inRange = 0;
	int num;

	while (fgets(buffer, 100, stdin) != NULL) {
		for (int i=0; i < strlen(buffer); i++) {
			//this section works the same as letter
			if (commands[commandsIndex] > 47) {
				num = convertToInt(commands, commandsIndex);
			}
			if (commands[commandsIndex] == '-') {
				inRange = 1;
				upperBound = convertToInt(commands, commandsIndex+1);
				commandsIndex++;
			}	
			if (column > upperBound){
				inRange = 0;
			}
			if (commands[commandsIndex] == ',') {
				commandsIndex++;
				num = convertToInt(commands, commandsIndex);
			} 
			//
			if (column == num || inRange == 1) {
				//a whitespace char will be printed later
				//so don't double print it
				if (buffer[i] != '\n') {
					printf("%c", buffer[i]);
				}
				// if the current char is a space move to the next
				// section of the command
				if (isASpace(buffer[i])) {
					commandsIndex++;

					if (num > 9) {
						commandsIndex++;
					}
				}
			} 
			if (buffer[i] == '\n') {
				// these values need to be reset for each new line
				column = 1;
				commandsIndex = 0;
				inRange = 0;
			} 
			// if a space is encountered move on to the next column
			if (isASpace(buffer[i])) {
				column += 1;
			}
		}
		printf("\n");
	}
}


/*
 * This function splits the given input on commos. It takes an array that will hold
 * up to 100 chars read in and an array containing the column numbers to print.
 */
void comma(char buffer[], char commands[]) {
	int commandsIndex = 0;
	int column = 1;
	int upperBound;
	int inRange = 0;
	int num;
	
	while (fgets(buffer, 100, stdin) != NULL) {
		for (int i=0; i < strlen(buffer); i++) {
			//this section works the same as letter
			if (commands[commandsIndex] > 47) {
				num = convertToInt(commands, commandsIndex);
			}
			if (commands[commandsIndex] == '-') {
				inRange = 1;
				upperBound = convertToInt(commands, commandsIndex+1);
				commandsIndex++;
			}	
			if (column > upperBound){
				inRange = 0;
			}
			if (commands[commandsIndex] == ',') {
				commandsIndex++;
				num = convertToInt(commands, commandsIndex);
			} 
			//
			if (column == num || inRange == 1) {
			       // print the chars excpet for commas and newlines	
				if (buffer[i] != ',' && buffer[i] != '\n') {
					printf("%c", buffer[i]);
				// if a comma is found advance to the next part of the command	
				} else {
					printf(" ");
					commandsIndex++;

					if (num > 9) {
						commandsIndex++;
					}
				}
			} 
			if (buffer[i] == '\n') {
				printf("\n");
				// these values need to be reset for each new line
				column = 1;
				commandsIndex = 0;
				inRange = 0;
			} 
			// if a comma is found move to the next column
			if (buffer[i] == ',') {
				column += 1;
			}
		}
	}
}

/* 
 * This function performs error checking on the input from the scut command
 * if the selection contains non-numeric characters excluding - and , it will exit
 * with a non zero status.
 */
int checkInput(char input[], int inputLen) {
	int intValue;
	// check that the first and last chars are digits
	if (input[0] < 48 || input[0] > 57) {
		fprintf(stderr, "Invalid selection.\n");
		return 1;
	} else if (input[inputLen-1] < 48 || input[inputLen-1] > 57) {
		fprintf(stderr, "Invalid selection.\n");
		return 1;
	}
	// check each character's acii code to make sure it is
	// a digit or , or -
	for (int i = 1; i < inputLen - 1; i++) {
		intValue = input[i];

		if (intValue == 45 || intValue == 44) {
			continue;
		} else if (intValue > 47 && intValue < 58) {
			continue;
		} else {
			fprintf(stderr, "Invalid selection.\n");
			return 1;
		}
	}
	return 0;
}
