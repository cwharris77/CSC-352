/**
 * tq.c
 * Author Cooper Harris
 * Course: CSC 352
 * 
 * This program implements functions from the tq.h header file to build, populate, print and free
 * a TQDecision tree. It expects one command line argument, the name of a file to build the tree from
 * that should be formatted like:
 * 10 
 * does it have 4 legs?,does it have wheels?,does it have a motor?,does it have fur? 
 * car,0,1,1,0
 * fox,1,0,0,1 
 * elephant,1,0,0,0 
 * trailer,0,1,0,0 
 * tarantula,0,0,0,1 
 * mirror,0,0,0,0 
 * work bench,1,1,0,0 
 * standing desk,1,1,1,0 
 * bear,1,0,0,1 
 * lion,1,0,0,1
 *
 * Where the first line is the number of items, the next is the questions the tree should store, and any following should be the
 * name of an object and a path to reach it where 1 is yes and 0 is no.
 *
 * The file may contain any number of objects and questions
 */
 
#include "tq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int numQuestions, numItems;

void build_helper(TQDecisionTreeNode* node, char* question);
void print_helper(TQDecisionTreeNode* root, char*typeString, int level, bool indent);
void free_helper(TQDecisionTreeNode* node);
char* read_line(FILE* file);
void populate_helper(TQDecisionTreeNode* root, char* object, int* directions, int index); 

void TQ_print_tree(TQDecisionTree* root) {
	if (root == NULL) {
		return;
	}

	print_helper(root->root, "", 0, false);
}
 
/**
 * This function is a helper method for printing the tree and handles the recursion for
 * traversing through the tree. It prints the tree using an in order traversal to match
 * the spec.
 *
 * It takes a pointer to a TQ_DecsionTreeNode, a string showing which type of node (yes or no) the given
 * node is, an integer representing what level of the tree the function is currently printing, and a boolean
 * to determine if an indent should be printed as parameters.
 */
void print_helper(TQDecisionTreeNode* root, char* typeString, int level, bool indent) {	
	if (root == NULL) {
		return;
	} 
	
	if (strcmp(root->text, "") == 0) {
		printf("%*s%s%s", level*4, "", typeString, root->text);

		for (int i = 0; i < root->num_answers; i++) {
			printf("| %s ", root->answers[i]);
		}
		if (root->num_answers != 0) {
			printf("|");
		}
		printf("\n");
	} else {
		printf("%*s%s[%s]\n", level*4, "", typeString, root->text);
	}
	if (indent == true) {
		print_helper(root->yes, "-y-> ", level + 1, true);
		print_helper(root->no, "-n-> ", level + 1, true);
	} else {
		print_helper(root->yes, "-y-> ", level, true);
		print_helper(root->no, "-n-> ", level, true);
	}
}

TQDecisionTree* TQ_build_tree(char* file_name) {
	FILE* inputFile = fopen(file_name, "r");
	char* numItemsLine = NULL;
	char* questions = NULL;
	
	// Make a new decision tree pointer
	TQDecisionTree* tree = calloc(sizeof(TQDecisionTree), 1);
	
	// make a node for the root and set it as the root of the tree
	TQDecisionTreeNode* root = calloc(sizeof(TQDecisionTreeNode), 1);
	tree->root = root;
	
	// The Number of Items
    	numItemsLine = read_line(inputFile);
	numItems = atoi(numItemsLine);

	// The line with questions
    	questions = read_line(inputFile);
	
	// split the questions string on a comma and copy it into the root text
	char *token = strtok(questions, ",");
	
	// If there are no questions
	if (token == NULL) {
		return NULL;
	}
	numQuestions = 1;
	strcpy(root->text, token); 
       	token = strtok(NULL, ",");

	// go to the next item in the split
	while (token != NULL) {
		// If the question has a newline at the end of it replace it with a null terminator
		for (int i = 0; token[i] != '\0'; i++) {
			if (token[i] == '\n' || (token[i] == ' ' && token[i-1] == '?')) {
				token[i] = '\0';
				break;
			}
		}
		
		build_helper(root, token);
		
		numQuestions++;

		token = strtok(NULL, ",");
    	}
	// Make the leaf nodes
	build_helper(root, "");

	free(numItemsLine);
	free(questions);
	fclose(inputFile);

	return tree;
}

/* 
 * This function builds the decision tree recursively and allocates
 * space for the nodes if the child is NULL and copies the question text
 * into the nodes text. 
 */
void build_helper(TQDecisionTreeNode* node, char* question) {
	if (node->yes != NULL) {
		build_helper(node->yes, question);
	} else {
		TQDecisionTreeNode* n = calloc(sizeof(TQDecisionTreeNode), 1);
		strcpy(n->text, question);
		n->num_answers = 0;

		node->yes = n;
	}
	
	if (node->no != NULL) {
		build_helper(node->no, question);
	} else {
		TQDecisionTreeNode* n = calloc(sizeof(TQDecisionTreeNode), 1);
		strcpy(n->text, question);
		n->num_answers = 0;

		node->no = n;
		return;
	}
		
}

/*
 * A helper function to read a buffer of any length by resizing it once
 * the buffer is full. It takes a pointer to a file as a parameter.
 */
char* read_line(FILE *file) {
    // Pointer to the buffer to hold the line
    char *buffer = NULL; 
    // Character read from the file
    char c; 
    // buffer size
    size_t bufsize = 0;
    // length of the line
    size_t len = 0;
    
    while ((c = fgetc(file)) != EOF && c != '\n') {
    	// resizing the buffer by adding 64 bytes when it is full
        if (len + 1 >= bufsize) {
            bufsize += 64;
	    // reallocate the space for the buffer
            buffer = realloc(buffer, bufsize);
        }
        
        buffer[len++] = c;
    }
    
    // Return null if all input lines were empty  
    if (len == 0 && c == EOF) { 
        return NULL;
    }
    
    // Null terminate the string
    buffer[len] = '\0';
    
    return buffer; 
}


void TQ_populate_tree(TQDecisionTree* tree, char* file_name) {
	if (tree == NULL) {
		return;
	}

	FILE* file = fopen(file_name, "r");
	
	// Advance to the lines holding answers
	char* curLine = read_line(file);
	free(curLine);
	
	curLine = read_line(file);
	free(curLine);

	char *token;

	while ((curLine = read_line(file)) != NULL) {
		token = strtok(curLine, ",");
	
		int i = 0;
		
		// Allocate space for the array that will hold the item and copy
		// The item into it
		char* curObj = malloc(strlen(token) + 1);
		strcpy(curObj, token);
		
		int directions[numQuestions + 1];

       		// Advance to the first integer
		token = strtok(NULL, ",");
		
		// Convert each yes/no direction into an int
		while (token != NULL) {
			directions[i] = atoi(token);

			i++;
       			token = strtok(NULL, ",");
		}
		// So the helper knows when to stop
		directions[i] = -1;
		populate_helper(tree->root, curObj, directions, 0);
		
		// Clean up the memory allocated
		free(curLine);
		free(curObj);
	}

	fclose(file);
}

/*
 * Recursivley traverses the tree following the yes path if the current direction is yes
 * and the no path otherwise until it reaches a leaf node. It then allocates space for 
 * the nodes answers pointer and each array that will hold an answer.
 *
 * It takes the current node in the tree, a string containing the item to be inserted, an array of
 * ints that holds the 1s and 0s representing yes or no, and the current index into that array as
 * parameters.
 */
void populate_helper(TQDecisionTreeNode* root, char* object, int* directions, int index) {
	// Leaf Node
	if (root->yes == NULL && root->no == NULL) {
		if (root->answers == NULL) {
			root->answers = calloc(sizeof(char*), numItems + 1);
		}
	
		root->answers[root->num_answers] = malloc(sizeof(char) * strlen(object) + 1);
		strcpy(root->answers[root->num_answers], object);
		root->answers[root->num_answers + 1] = NULL;

		root->num_answers++;
	
		return;
	}

	if (directions[index] == 1) {
		populate_helper(root->yes, object, directions, index+1);
	} else {	
		populate_helper(root->no, object, directions, index+1);
	}

}

void TQ_free_tree(TQDecisionTree* tree) {
	free_helper(tree->root);
	free(tree);
}

/*
 * Helper method to handle recursing down the tree and freeing
 * the contents of the array of answers in each node then the pointer to the array 
 * and then the pointer to the node itself. 
 */
void free_helper(TQDecisionTreeNode* node) {
	if (node == NULL) {
		return;
	}

	free_helper(node->yes);
	free_helper(node->no);

	for (int i = 0; i < node->num_answers; i++) {
		free((node->answers)[i]);
	}

	free(node->answers);
	free(node);
}
