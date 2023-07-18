/*  This program generates a report about NBA basketball players, based on data that 
 *  it reads in from a text file. It expects input in the form:
 *  PLAYER_NAME[P1, R1, A1][P2, R2, A2],...,[PN, RN, AN] where each set of brackts represents one game.
 *
 *  Other things the program expects: 
 *  A player name will not be longer than 50 characters. 
 *  A player will never have 100 or more points, rebounds, or assists in a single game.
 *  A given line will not have more than 100 games on it
 *  The file will contain 100 players (lines) or less
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arrayz.h"
#include <ctype.h>


struct player {
	char name[51];
	long points[101];
	long rebounds[101];
	long assists[101];
	
	double meanPoints;
	double meanRebounds;
	double meanAssists;

	double sdPoints;
	double sdRebounds;
	double sdAssists;
};

typedef struct player Player;

void readFile(FILE* statsFile, Player playerList[]);
void fillPlayerStats(Player *player1, char token[]);
void calculateCategories(Player playerList[]);


// the current index into each array of the player struct
int pointsIndex, reboundsIndex, assistsIndex;
int playerListLen = 0;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fprintf(stderr, "expects 1 command line argument");

		return 1;
	}

	FILE *statsFile = fopen(argv[1], "r");

	Player *playerList = calloc(100, sizeof(Player));
	
	readFile(statsFile, playerList);
			
	calculateCategories(playerList);

	free(playerList);

	fclose(statsFile);

	return 0;
}

/* This function takes a pointer to a text file containing well
   formatted input and an array with space for 100 player structs as
   arguments. It reads through each line of the file and splits the input
   by player name and each game stats. It then puts the new player in the 
   player list
*/
void readFile(FILE *statsFile, Player playerList[]) {	
	char buffer[851];
	int playerListIndex = 0;
	
	for (playerListIndex = 0; fgets(buffer, 851, statsFile) != NULL; playerListIndex++) {
		Player player1;
		
		// initialize the arrays to show that there are currently zero
		// elements after the first index
		player1.points[0] = 0;
		player1.rebounds[0] = 0;
		player1.assists[0] = 0;
	
		pointsIndex = 1;
		reboundsIndex = 1;
		assistsIndex = 1;
		
		// split the string using "[" and "]"
		char *token = strtok(buffer, "[]"); 
		int count = 0; 
		
		strcpy(player1.name, token);

    		while (token != NULL) { 
			//printf("%s\n", token);
        		if (count == 0) { // ignore the first split 
            			token = strtok(NULL, "[");
            			count++;
            			continue;
        		}

        		fillPlayerStats(&player1, token);

        		token = strtok(NULL, "["); // get the next split
        		count++;
    		}

		player1.meanPoints = mean(player1.points);
		player1.meanRebounds = mean(player1.rebounds);
		player1.meanAssists = mean(player1.assists);

		player1.sdPoints = sdev(player1.points);
		player1.sdRebounds = sdev(player1.rebounds);
		player1.sdAssists = sdev(player1.assists);
	
		playerList[playerListIndex] = player1;
		playerListLen++;
	}
}


/* This function takes a pointer to a player struct and a string representing
   the current game stats. It fills the fields of the player struct with the
   game stats in place.
*/
void fillPlayerStats(Player *player1, char token[]) {
	int j = 0, statsIndex = 0;	
	int stats[3] = {0, 0, 0};
	char stat[3];
	stat[2] = '\0';

	while (token[j] != '\0') {
		if (isdigit(token[j]) != 0 && isdigit(token[j+1]) != 0) {
			stat[0] = token[j];
			stat[1] = token[j+1];
			stats[statsIndex] = atoi(stat);
			j++;
		} else if (isdigit(token[j]) != 0) {
			stat[0] = token[j];
			stat[1] = '\0';
			stats[statsIndex] = atoi(stat);
		} else {
			statsIndex--;
		}

		statsIndex++;
		if (statsIndex > 2) {
			statsIndex = 0;
		}
		j++;
    	}

	player1->points[0]++;
	player1->rebounds[0]++;
	player1->assists[0]++;

	player1->points[pointsIndex] = stats[0];
	player1->rebounds[reboundsIndex] = stats[1];
	player1->assists[assistsIndex] = stats[2];
	
	player1->meanPoints = mean(player1->points);
	player1->meanRebounds = mean(player1->rebounds);
	player1->meanAssists = mean(player1->assists);

	player1->sdPoints = sdev(player1->points);
	player1->sdRebounds = sdev(player1->rebounds);
	player1->sdAssists = sdev(player1->assists);
	
	pointsIndex++;
	reboundsIndex++;
	assistsIndex++;
}

/* This function takes a list of player structs as an argument and loops
   through it to calculate the best, worst, most and least consistent scorers,
   rebounders, and assisters for each category.
*/
void calculateCategories(Player playerList[]) {
	double sdevPoints[playerListLen + 1];
	double sdevReb[playerListLen + 1];
	double sdevAssists[playerListLen + 1];

	double meanPoints[playerListLen + 1];
	double meanReb[playerListLen + 1];
	double meanAssists[playerListLen + 1];
	
	sdevPoints[0] = 0;
	sdevReb[0] = 0;
	sdevAssists[0] = 0;

	meanPoints[0] = 0;
	meanReb[0] = 0;
	meanAssists[0] = 0;
	
	int j = 1;
	for (int i = 0; i < playerListLen; i++) {
		sdevPoints[j] = playerList[i].sdPoints;
		sdevPoints[0]++;
		
		sdevReb[j] = playerList[i].sdRebounds;
		sdevReb[0]++;

		sdevAssists[j] = playerList[i].sdAssists;
		sdevAssists[0]++;

		meanPoints[j] = playerList[i].meanPoints;
		meanPoints[0]++;

		meanReb[j] = playerList[i].meanRebounds;
		meanReb[0]++;
		
		meanAssists[j] = playerList[i].meanAssists;
		meanAssists[0]++;

		j++;
	}	
	printf("most consistent scorer: %s\n", playerList[minid(sdevPoints) - 1].name); 
	printf("most inconsistent scorer: %s\n", playerList[maxid(sdevPoints) - 1].name);

	printf("highest scorer: %s\n", playerList[maxid(meanPoints) - 1].name);
	printf("lowest scorer: %s\n", playerList[minid(meanPoints) - 1].name);
	
	printf("most inconsistent rebounder: %s\n", playerList[maxid(sdevReb) - 1].name);
	printf("most consistent rebounder: %s\n", playerList[minid(sdevReb) - 1].name);
	
	printf("highest rebounder: %s\n", playerList[maxid(meanReb) - 1].name);
	printf("lowest rebounder: %s\n", playerList[minid(meanReb) - 1].name);
	
	printf("most inconsistent assister: %s\n", playerList[maxid(sdevAssists) - 1].name);
	printf("most consistent assister: %s\n", playerList[minid(sdevAssists) - 1].name);
	
	printf("lowest assister: %s\n", playerList[minid(meanAssists) - 1].name);
	printf("highest assister: %s\n", playerList[maxid(meanAssists) - 1].name);
}




