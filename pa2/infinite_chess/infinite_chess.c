/*
 * infinite_chess.c
 * Author: Cooper Harris
 * Course: CSC 352
 *
 * This program takes user input to select a piece (king, brigadier, pawn),
 * and a number of moves then prints how many possible locations the piece
 * could be in.
 */

#include <stdio.h>

int main() {
  char piece;
  int  numMoves, possiblePositions;

  printf("Enter piece type (k, b, p):\n");
  scanf("%c", &piece);

  printf("Enter number of moves:\n");
  scanf("%d", &numMoves);

  int pawnMove();
  int kingMove();
  int brigadierMove();

  if (piece == 'p'){
    possiblePositions = pawnMove(numMoves);
  } else if (piece == 'k'){
    possiblePositions = kingMove(numMoves);
  } else {
    possiblePositions = brigadierMove(numMoves);
  }

  printf("possible locations: %d\n", possiblePositions);
  
  return 0;
}

/*
* A function to calculate how many places a pawn could be
*/
int pawnMove(int moves){
  return moves + 1;
}

/*
* A function to calculate how many places a king could be with
* the given number of moves
*/
int kingMove(int moves){
  return (moves*2 + 1) * (moves*2 + 1) ;
}

/*
* A function to calculate how many places a brigadier could be with
* the given number of moves. A brigadier may move to any of its
* four neighboring diagonal spaces but may not move forwards, backwards,
* left or right.
*/
int brigadierMove(int moves){
  if (moves == 0){
    return 1;
  } else {
    return brigadierMove(moves - 1) + 4*moves;
  }

}

