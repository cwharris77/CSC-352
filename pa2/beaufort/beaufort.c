/*
 * beaufort.c
 * Author: Cooper Harris
 * Course: CSC 352
 *
 * This program takes input from the command line
 * and encrypts it using the beaufort cipher.
 * Valid input is expexted and must be in the format
 *
 * ENCRYPTIONKEY
 * INPUT
 *
 * Where input can be as many lines as you want, but 
 * each line may only take 128 characters.
 */

#include <stdio.h>
#include <string.h>

int getIndex(char character);
void printEncrypted();


const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";

int main() {
    char input[128], key[128];
    int  firstRun = 1;
    int  keyLen, plainIndex, keyIndex, encryptIndex, keyPosition = 0;

    while (fgets(input, 128, stdin) != NULL){
        // break when a blank line is entered
        if (input[0] == '\n' && input[1] == '\0'){
            break;
        }
        // check to see if the key array needs to be created;
        if (firstRun == 1){
            keyLen = strlen(input);

            int j = 0;
            while (j <= strlen(input)){
                key[j] = input[j];
                j += 1;
            }
            firstRun = 0;
        } else {
            int i = 0;
            while (i < strlen(input)) {
                //carry over the key if the input is longer than it
                if (keyPosition == keyLen - 1){
                    keyPosition = 0;
                }
                if (input[i] == ' ' || input[i] == '\0' || input[i] == '\n') {
                    printf(" ");
                } else {
                    /*these are the indeces the the char input[i] are found
                      at in the alphabet
                    */ 
                    plainIndex = getIndex(input[i]);
                    keyIndex   = getIndex(key[keyPosition]);

                    // alphabet index of the encryption character
                    // encrypt letterIndex = index of key - index of plain text letter
                    encryptIndex = keyIndex - plainIndex;
                    /*if the key character is earlier in the alphabet
                      than the input character make the index positve
                      by adding the length of the alphabet array
                    */

                    if (encryptIndex < 0){
                        encryptIndex = 26 + encryptIndex;
                    }
                    // print the encrypted character
                    printf("%c", alphabet[encryptIndex]);
                    // increment the position in the key
                    keyPosition += 1;
                }
                i += 1;
            }
            printf("\n");
        }
    }
    return 0;
}

/*
  Calculates the index of a given char in the alphabet array and
  returns it.
*/
int getIndex(char character){
    char* charPointer = strchr(alphabet, character);

    // The index the given char was found at is
    // the pointer to it - the pointer to the start
    // of the char array
    int index = charPointer - alphabet;

    return index;
}
