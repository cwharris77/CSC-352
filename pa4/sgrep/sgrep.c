/*
 * sgrep.c
 * Author: Cooper Harris
 * Course: CSC 352
 *
 * This program is a simplified version of the grep command. 
 * input should be include only one search term with no spaces but
 * the flags may be placed anywhere after the executable name
 * where options may be -o, -i, or -e.
 * ex ./sgrep -o -i pa.s -e
 * -o will print only the input that matches the search term
 * -i is case insensitive search
 * -e allows for pattern search where a . represents any char
 * and # mathces any number of chars in bewteen the given chars
 * ex s#i#ca...n matches specification
 *
 */

#include <stdio.h>
#include <string.h>

void search(char searchWord[], int oEnabled, int iEnabled, int eEnabled);
int  checkFormat(char searchWord[]);
int  charType(char c);
void toUpperCase(char word[]);
int mycomp(char* searchString, char* givenString);

	
int main(int argc, char * argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Requires more command-line arguments.\n");

		return 1;
	}

	int oEnabled = 0;
	int iEnabled = 0;
	int eEnabled = 0;
	int searchWordPos;
	int correctFormat = 0;

	for (int i=0; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			oEnabled = 1;
		} else if (strcmp(argv[i], "-i") == 0) {
			iEnabled = 1;
		} else if (strcmp(argv[i], "-e") == 0) {
			eEnabled = 1;
		} else {
			searchWordPos = i;
		}
	}
	if (eEnabled == 1) {
		// check the formatting of the given search term
		correctFormat = checkFormat(argv[searchWordPos]);
		
		if (correctFormat != 0) {
			fprintf(stderr, "Invalid search term.\n");
			return 1;
		}
	}
	search(argv[searchWordPos], oEnabled, iEnabled, eEnabled);
	return 0;
}

/*
 * This function handles searching the given input for matches to the search pattern
 * it takes the search word and the ints showing if the various flags are enabled as
 * arguments.
 * When it finds a match it prints it to stdout.
 *
 */
void search(char searchWord[], int oEnabled, int iEnabled, int eEnabled) {
	char buffer[200];
	char curWord[200];
	char printWord[200];
	char upperBuffer[200];
	
	int searchIndex = 0;
	int curIndex = 0;
	char bufferChar;
	// 1 if the current search word char is a #
	int inPattern = 0;
	// if case insensitive search is on convert the search term to uppercase
	if (iEnabled == 1) { 
		toUpperCase(searchWord);
	} 
	while (fgets(buffer, 200, stdin) != NULL) {
		// copy the current buffer and uppercase it because the
		// original buffer char will be printed if a match is found
		if (iEnabled == 1) { 
			strcpy(upperBuffer, buffer);
			toUpperCase(upperBuffer);
		}
		// reset the search to the first chars
		curIndex = 0;
		searchIndex = 0;
		for (int i = 0; i < strlen(buffer); i++) {
			if (iEnabled == 1) {
				bufferChar = upperBuffer[i];
			} else {
				bufferChar = buffer[i];
			}
			if (eEnabled == 1 && searchWord[searchIndex] == '#') {
				// if the letter directly after the # is found
				// it is no longer in a pattern
				if (bufferChar == searchWord[searchIndex+1] ) {
					inPattern = 0;
					searchIndex++;
			
				} else {
					inPattern = 1;
				}
			} 
			if (bufferChar == searchWord[searchIndex] || searchWord[searchIndex] == '.' || inPattern == 1) {
				curWord[curIndex] = bufferChar;
				printWord[curIndex] = buffer[i];
				// the index should only be incremented when the character is
				// not a #
				if (inPattern == 0) {
					searchIndex++;
				}
				curIndex++;
			// this means a match was not found and the indeces should be reset
			} else {
				searchIndex = 0;
				curIndex = 0;
			}			
			// null terminate the current word so string operations can be performed
			curWord[curIndex] = '\0';
			printWord[curIndex] = '\0';
			
			if (mycomp(searchWord, curWord) == 0) {
				// print the whole line if exact match is off
				if (oEnabled == 0) {
					printf("%s", buffer);
					// the line should no be printed again if another match is found
					// so end checking for this line
					break;
				} else {
					printf("%s\n", printWord);
					// "clear" the word so a match is not double counted
					curWord[0] = '\0';
				}
			}
		}
	}
}

/*
 * This function compares two strings and returns 0 if they are equal
 * It accounts for the . and # chars in the pattern search.
 *
 */
int mycomp(char* searchString, char* givenString) {
    int searchLength = strlen(searchString);
    int givenLength = strlen(givenString);
    int i, j;

    if (searchLength > givenLength) {
        return 1;
    }

    for (i = 0, j = 0; i < searchLength; i++, j++) {
        // . counts as any character so skip to the next one
	if (searchString[i] == '.') 
        {
            continue;
        }
        else if (searchString[i] == '#') {
		// advance to the next searchString char
		i++;
		// move to the next char in the search string until the char after the # is found
            	while (givenString[j] != searchString[i]) {
		    	j++;
            	}
		//this means that the character to end the pattern was never found
		if (j >= givenLength) {
			return 1;
		}
        }
        else if (searchString[i] != givenString[j]) {
            return 1;
        }
    }
    return 0;
}

/*
 * A function to check the formatting of the given search pattern.
 * it makes sure every # char is preceeded and followed by a letter.
 * It takes the char array to check as an argument.
 *
 */
int  checkFormat(char searchWord[]) {
	// if the first character is a hashtag
	if (searchWord[0] == '#') {
		return 1;
	}
	int len = strlen(searchWord);
	int i = 1;
       	while (i<len) {
		int curType = charType(searchWord[i]);
		int nextType = charType(searchWord[i+1]);
		// if the char is a hashtag and the next char isnt a letter
		if (curType == 0 && (nextType != 2 && nextType != 3)) {
			return 1;
		// if the char is a . and the next char is a #
		} else if (curType == 1 && nextType == 0) {
			return 1;
		}
		i++;
	}		

	return 0;
}

/*
 * This function returns an int representing the type of char
 * that was passed in.
 */
int charType(char c) {
	if (c == '\n' || c == '\0') {
		return -1;
	} else if (c == '#') {
		return 0;
	} else if (c == '.') {
		return 1;
	} else if (c >= 'A' && c <= 'Z') {
		return 2;
	} else if (c >= 'a' && c <= 'z') {
		return 3;
	} else {
		return 4;
	}
}

/* 
 * This function takes a char array and turns
 * all the alphabetical characters to their
 * uppercase verion
 */
void toUpperCase(char word[]) {
	int len = strlen(word);

	for (int i=0; i < len; i++) {
		if (charType(word[i]) == 3) {
		// if the char is a lowercase lettere
		// change the ascii value to the uppercase
		// version
			char  newChar = word[i] - 32;
			word[i] = newChar;
		}
	}
}


