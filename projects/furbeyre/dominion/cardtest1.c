/*
 * cardtest1.c -- SMITHY
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "SMITHY"
int numPass = 0;
int numFail = 0;

void testResult(int exp, int act, char* desc) {
    printf("|  %-64s  ", desc);
    printf("|  Expected: %2d  |   Actual: %2d  |  Result:  ", exp, act);
    if (exp == act){
        printf("PASS  |\n");
        numPass++;
    } else {
        printf("FAIL  |\n");
        numFail++;
    }
}

void resetGame(int numPlayer, int* k, int seed, struct gameState* G) {
    memset(G, 0, sizeof(struct gameState));    // clear the game state
    initializeGame(numPlayer, k, seed, G);     // initialize a new game
}

int main() {
    int g, p, n;
    char desc[128];
    int seed = 1000;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf("\n************************************************* Testing SMITHY *************************************************\n");

    printf("\n--------------------------------------------- Smithy Effect After Game Init ----------------------------------------------\n");
    for (g = 2; g <= 4; g++) {      // for each possible number of players in the game
        for (p = 0; p < g; p++) {       // for each player in the game
            for (n = 0; n < 5; n++) {       // for each potential position of card in hand
                resetGame(g, k, seed, &G);
                memcpy(&testG, &G, sizeof(struct gameState));
                G.whoseTurn = p;
                cardEffect(smithy, 0, 0, 0, &G, n, 0);
                sprintf(desc, "%d Players, P%d, Card position %d,   new hand count is 2 more", g, p+1, n);
                testResult(testG.handCount[p]+2, G.handCount[p], desc);
                sprintf(desc, "%d Players, P%d, Card position %d,   new deck count is 3 less", g, p+1, n);
                testResult(testG.deckCount[p]-3, G.deckCount[p], desc);
                sprintf(desc, "%d Players, P%d, Card position %d, new played count is 1 more", g, p+1, n);
                testResult(testG.playedCardCount+1, G.playedCardCount, desc);
            }
        }
    }


    printf("\n-------------------------------------------- Hand Content And Card Positioning -------------------------------------------\n");
    int handPos;

    resetGame(4, k, seed, &G);
    int hand1[5] = {copper, estate, smithy, silver, adventurer};
    printf("--- Hand Before Playing Smithy: copper, estate, smithy, silver, adventurer ---\n");
    memcpy(G.hand[0], hand1, sizeof(int) * 5);
    G.handCount[0] = 5;
    G.whoseTurn = 0;
    handPos = 2;
    cardEffect(smithy, 0, 0, 0, &G, handPos, 0);
    testResult(7, G.handCount[0], "Hand Count Should be 7");
    testResult(copper, handCard(0, &G), "Card in position 0 should be copper");
    testResult(estate, handCard(1, &G), "Card in position 1 should be estate");
    testResult(silver, handCard(3, &G), "Card in position 3 should be silver");
    testResult(adventurer, handCard(4, &G), "Card in position 4 should be adventurer");

    resetGame(4, k, seed, &G);
    int hand2[5] = {smithy, gold, curse};
    printf("--- Hand Before Playing Smithy: smithy, gold, curse ---\n");
    memcpy(G.hand[0], hand2, sizeof(int) * 3);
    G.handCount[0] = 3;
    G.whoseTurn = 0;
    handPos = 0;
    cardEffect(smithy, 0, 0, 0, &G, handPos, 0);
    testResult(5, G.handCount[0], "Hand Count Should be 5");
    testResult(gold, handCard(1, &G), "Card in position 1 should be gold");
    testResult(curse, handCard(2, &G), "Card in position 2 should be curse");

    resetGame(4, k, seed, &G);
    int hand3[7] = {gardens, village, mine, council_room, copper, estate, smithy};
    printf("--- Hand Before Playing Smithy: gardens, village, mine, council_room, copper, estate, smithy ---\n");
    memcpy(G.hand[0], hand3, sizeof(int) * 7);
    G.handCount[0] = 7;
    G.whoseTurn = 0;
    handPos = 6;
    cardEffect(smithy, 0, 0, 0, &G, handPos, 0);
    testResult(9, G.handCount[0], "Hand Count Should be 9");
    testResult(gardens, handCard(0, &G), "Card in position 0 should be gardens");
    testResult(village, handCard(1, &G), "Card in position 1 should be village");
    testResult(mine, handCard(2, &G), "Card in position 2 should be mine");
    testResult(council_room, handCard(3, &G), "Card in position 3 should be council_room");
    testResult(copper, handCard(4, &G), "Card in position 4 should be copper");
    testResult(estate, handCard(5, &G), "Card in position 5 should be estate");

    printf("\n\n ***** %s TESTS: PASSED %d OUT OF %d TESTS ***** \n\n", TESTCARD, numPass, numPass+numFail);
	return 0;
}
