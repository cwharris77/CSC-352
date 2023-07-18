/**
 * tq.h
 * Author: Cooper Harris
 * Course: CSC 352
 * 
 * This header file defines structs for a binary tree called a TQDecisionTree.
 * Each tree contains a pointer to its root node. The nodes define their children 
 * as yes and no.
 * 
 * It also defines several functions that can be used to create and detroy
 * TQDecision trees.
 */

typedef struct TQDecisionTreeNode { 
	char text[50]; 
	int num_answers; 
	char** answers; 
	struct TQDecisionTreeNode* yes; 
	struct TQDecisionTreeNode* no; 
} TQDecisionTreeNode;

typedef struct TQDecisionTree { 
	TQDecisionTreeNode* root; 
} TQDecisionTree;

/*
 * This function prints out a text representation of a decision tree with four space
 * indents to represent the levels
 */
void TQ_print_tree(TQDecisionTree* root);

/* This function accepts a char* which represents the name of the file to load the data from. The function then opens up the file, 
 * iterate through the data within and populates a decision tree. The answers are not added to the tree, just the question structure and 
 * leaf nodes with no questions or answers. It returns a TQDecisionTree that has been populated with all of the questions. Every level of 
 * this totally-full tree should has the same question. One particular path through the tree from root to leaf represents one possible 
 * sequence of the user answers yes/no to the presented questions
 */
TQDecisionTree* TQ_build_tree(char* file_name);

/*This function takes a previously-built tree and a char* with the name of the data file. The function populates the tree with the answers within 
* the correct leaf nodes based on the data from the file, following the correct yes/no paths through the tree. This function does not *add* any new 
* nodes to the tree. Rather, it only adds possible answers to the leaf nodes of the tree that is passed into it
*/
void TQ_populate_tree(TQDecisionTree* tree, char* file_name);

/*
 * This function takes a TQDecisionTree and frees all memory associated with the tree
 */
void TQ_free_tree(TQDecisionTree* tree);
