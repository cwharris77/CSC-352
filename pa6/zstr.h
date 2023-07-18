typedef char* zstr;
typedef int zstr_code;

#define ZSTR_OK       0 
#define ZSTR_ERROR    100
#define ZSTR_GREATER  1 
#define ZSTR_LESS    -1 
#define ZSTR_EQUAL    0

/*
This function creates a zstr from a given string. It allocates 
memory for the new zstr using malloc and returns the zstr. The
zstr's memory has space for two integers then the given string
then any bytes that are left over such as:

--------------------------------------------------------------------------------------------
| char array len (int) | Allocated size (int) | char array data | \0 | possible extra bytes |
--------------------------------------------------------------------------------------------
For any given zstr, the total
ALLOCATED_SPACE must be either 16, 32, 256, 1024, or 2048. Thus, 
for the purpose of this assignment, a zstr has a hard limit on the 
max number of characters it can contain (2048sizeof(int) * 2- 1)
*/
zstr zstr_create(char* initial_data);

/*
This function takes a zstr as an argument and uses
the free function to destroy it. Because the given zstr
points to the beginning of the data section it first finds
the true beginning of the zstr using pointer math
*/
void zstr_destroy (zstr to_destroy);

/* 
This function takes a pointer to a zstr which will act as the base zstr,
and a zstr containing the string content to append to the base zstr. The function 
should append the char array content from to_append into base (resizing base if necessary) 
and update the length and allocated size values as needed.
*/
void zstr_append (zstr * base, zstr to_append);

/* 
This function searches for the first occurrence of to_search within base. 
It returns the index if found, or -1 if not found. It returns the index based on the 
beginning of the actual char array.
*/
int zstr_index(zstr base, zstr to_search);

/*
This function counts how many times to_search appears within base. 
It returns 0 if no match is found.
*/
int zstr_count (zstr base, zstr to_search);

/*
This function compares two zstrs. It returns ZSTR_GREATER if x > y, ZSTR_EQUAL if x == y, and ZSTR_LESS if x < y. 
The function compares based on ascii character values, in the same way that strcmp does.
*/
int zstr_compare (zstr x, zstr y);

/*
This function prints out a zstr, with the size and allocated space values included.
*/
void zstr_print_detailed(zstr data);

zstr zstr_substring (zstr base, int begin, int end);
