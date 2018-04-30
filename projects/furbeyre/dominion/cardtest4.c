/*
 * cardtest3.c -- MINE
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

#define TESTCARD "FEAST"
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

int getHandCost(int player, struct gameState* G) {
    int i, totalCost = 0;
    for ( i = 0; i < G->handCount[player]; i++) {
        totalCost += getCost(G->hand[player][i]);
    }
    return totalCost;
}

int handContains(int card, int player, struct gameState* G) {
    int i;
    for ( i = 0; i < G->handCount[player]; i++ ) {
        if (G->hand[player][i] == card)
            return 1;
    }
    return 0;
}

int discardContains(int card, int player, struct gameState* G) {
    int i;
    for ( i = 0; i < G->discardCount[player]; i++ ) {
        if (G->discard[player][i] == card)
            return 1;
    }
    return 0;
}

void resetGame(int numPlayer, int* k, int seed, struct gameState* G) {
    memset(G, 0, sizeof(struct gameState));    // clear the game state
    initializeGame(numPlayer, k, seed, G);     // initialize a new game
}

int main() {
    int g, p, n, b; // Loop Counters
    int res;    // result variable
    char desc[128];
    int seed = 1000;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			feast, tribute, smithy, council_room};

    printf("\n****************************************************** Testing FEAST *************************************************\n");

    printf("\n---------------------------------------- Basic Tests (Cards That Can Be Bought) ----------------------------------------------\n");
    int startHand[5] = {copper, estate, copper, estate, copper};
    int buy[5] = {council_room, embargo, village, smithy, mine};
    for (g = 2; g <= 2; g++) {      // for each possible number of players in the game
        for (p = 0; p < g; p++) {       // for each player in the game
            for (n = 0; n < 5; n++) {       // for each potential position of card in hand
                for (b = 0; b < 5; b++) {       // for each potential card to buy
                    resetGame(g, k, seed, &G);
                    G.whoseTurn = p;
                    memcpy(G.hand[p], startHand, sizeof(int)*5);
                    G.handCount[p] = 5;
                    G.hand[p][n] = feast;
                    memcpy(&testG, &G, sizeof(struct gameState));
                    res = cardEffect(feast, buy[b], n, 0, &G, n, 0);
                    sprintf(desc, "%d Players, P%d, Card position %d, Buy card %2d, discard contains new  card", g, p+1, n, buy[b]);
                    testResult(1, discardContains(buy[b], p, &G), desc);
                    sprintf(desc, "%d Players, P%d, Card position %d, Buy card %2d, hand doesn't contain feast", g, p+1, n, buy[b]);
                    testResult(0, handContains(feast, p, &G), desc);
                    sprintf(desc, "%d Players, P%d, Card position %d, Buy card %2d, new hand count is one less", g, p+1, n, buy[b]);
                    testResult(4, G.handCount[p], desc);
                }
            }
        }
    }

    printf("\n---------------------------------------- Basic Tests (Cards That CANT Be Bought) ----------------------------------------------\n");
    int startHand2[5] = {copper, estate, copper, estate, copper};
    int buy2[5] = {adventurer, province, gold, outpost, sea_hag};
    for (g = 2; g <= 4; g++) {      // for each possible number of players in the game
        for (p = 0; p < g; p++) {       // for each player in the game
            for (n = 0; n < 5; n++) {       // for each potential position of card in hand
                for (b = 0; b < 5; b++) {       // for each potential card to buy
                    resetGame(g, k, seed, &G);
                    G.whoseTurn = p;
                    memcpy(G.hand[p], startHand2, sizeof(int)*5);
                    G.handCount[p] = 5;
                    G.hand[p][n] = feast;
                    memcpy(&testG, &G, sizeof(struct gameState));
                    res = cardEffect(feast, buy2[b], n, 0, &G, n, 0);
                    sprintf(desc, "%d Players, P%d, Card position %d, Buy card %2d, discard doesn't contain card", g, p+1, n, buy2[b]);
                    testResult(0, discardContains(buy2[b], p, &G), desc);
                    sprintf(desc, "%d Players, P%d, Card position %d, Buy card %2d,    hand still contains feast", g, p+1, n, buy2[b]);
                    testResult(1, handContains(feast, p, &G), desc);
                    sprintf(desc, "%d Players, P%d, Card position %d, Buy card %2d,   new hand count is the same", g, p+1, n, buy2[b]);
                    testResult(5, G.handCount[p], desc);
                }
            }
        }
    }

    printf("\n\n ***** %s TESTS: PASSED %d OUT OF %d TESTS ***** \n\n", TESTCARD, numPass, numPass+numFail);
	return 0;
}
