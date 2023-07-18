#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Devin Booker[25,5,7][27,8,5][29,5,5][28,3,10]";
    char *ptr = strtok(str, "[]"); // split the string using "[" and "]"
    int count = 0; // count the number of splits

    while (ptr != NULL) {
        if (count % 4 == 0) { // ignore the first split "Devin Booker"
            ptr = strtok(NULL, "[,]");
            count++;
            continue;
        }
        printf("%s\n", ptr); // print each split
        ptr = strtok(NULL, "[,]"); // get the next split
        count++;
    }

    return 0;
}

