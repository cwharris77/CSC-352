/**
 * game.c
 * Author: Cooper Harris
 * Course: CSC 352
 * 
 * This program is an implementation of a guessing game that the user plays with the computer.
 * It expects exactly one command line argument, the name of a file containing questions and
 * and items that can be made into a TQDecisionTree.
 *
 * It reads the file and calls functions to build the decision tree then recurses down the tree
 * using user input to determine which path to follow until it reaches a leaf node. If there are
 * questions in the node it loops through them and the game ends when the user answers yes to a question
 * or there are none left.
 */

#include <stdio.h>
#include <stdlib.h>
#include "tq.h"

void play_game(TQDecisionTreeNode* root);

int main(int argc, char* argv[]) {
	TQDecisionTree* gameTree = TQ_build_tree(argv[1]);
	TQ_populate_tree(gameTree, argv[1]);

	play_game(gameTree->root);
	
	TQ_free_tree(gameTree);

	return 0;
}

/*
 * This function takes a pointer to a TQDecisionNode as a parameter and recurses down the subtree that node is the root of.
 * It uses user input to determine the path until a leaf node is reached. It loops through the questions in the array contained
 * in the leaf node and ends the game when the user says it has found the correct item or it runs out of items in the answers array.
*/
void play_game(TQDecisionTreeNode* root) {
	if (root->yes == NULL && root->no == NULL) {
		for (int i = 0; root->answers != NULL && root->answers[i] != NULL; i++) {
			printf("is it a %s? (y/n)\n", root->answers[i]);

			char answer[2];
			scanf("%1s", answer);
			
			if (answer[0] == 'y' || answer[0] == 'Y') {
				printf("I guessed it!\n");
				return;
			} 
		}
		
		printf("You got me :)\n");

		return;
	}

	printf("%s (y/n)\n", root->text);

	char answer[2];

	scanf("%1s", answer);

	if (answer[0] == 'y' || answer[0] == 'Y') {
		play_game(root->yes);
	} else if (answer[0] == 'n' || answer[0] == 'N') {
		play_game(root->no);
	} else {
		printf("Invalid Answer\n");
		return;
	}
}
