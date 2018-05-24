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

#define TESTCARD "MINE"
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

int getFirst(int card, int player, struct gameState* G) {
    int i;
    for ( i = 0; i < G->handCount[player]; i++) {
        if (G->hand[player][i] == card) {
            return i;
        }
    }
    return -1;
}

int getHandCost(int player, struct gameState* G) {
    int i, totalCost = 0;
    for ( i = 0; i < G->handCount[player]; i++) {
        totalCost += getCost(G->hand[player][i]);
    }
    return totalCost;
}

int getRandInt(int low, int high) {
    return (rand() % (high-low+1) + low);
}

void getRandCards(int* arr, int size, int* pool, int pool_len) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = pool[getRandInt(0, pool_len-1)];
    }
}

void resetGame(int numPlayer, int* k, int seed, struct gameState* G) {
    memset(G, 0, sizeof(struct gameState));    // clear the game state
    initializeGame(numPlayer, k, seed, G);     // initialize a new game
}

int main() {
    int i, j, g, p, h, n, d, x; // Loop Counters
    char desc[128];
    int seed = 1000;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    int pool_len = 21;
    int pool[21] = {adventurer, embargo, village, minion, mine, cutpurse,
			     sea_hag, tribute, smithy, council_room,
                 copper, copper, copper, copper, copper, silver, gold,
                 estate, duchy, province, gardens};

    printf("\n****************************************************** Testing COUNCIL ROOM *************************************************\n");

    for (i = 1; i <= 100; i++) {
        g = getRandInt(2, 4);       // Get random number of players in game
        p = getRandInt(0, g-1);     // Get random player
        h = getRandInt(4, 9);      // Get random number of cards in hand
        d = getRandInt(10, 20);      // Get random number of cards in deck
        x = getRandInt(10, 20);      // Get random number of cards in deck
        n = getRandInt(0, h-1);       // Get random card position

        resetGame(g, k, seed, &G);

        // Set hand for each
        G.handCount[p] = h;
        getRandCards(G.hand[p], h, pool, pool_len);
        G.hand[p][n] = council_room;  // One of the cards in hand must be adventurer

        // Set deck
        G.deckCount[p] = d;
        getRandCards(G.deck[p], d, pool, pool_len);

        // Set discard
        G.discardCount[p] = x;
        getRandCards(G.deck[p], x, pool, pool_len);

        memcpy(&testG, &G, sizeof(struct gameState));       // Copy current game state
        G.whoseTurn = p;

        cardEffect(council_room, 0, 0, 0, &G, n, 0);

        printf("\n---------- Setup %d: %d Players, P%d, Hand Count %d, Card position %d, Deck Count %d, Discard Count %d ---------------\n", i, g, p+1, h, n, d, x);

        sprintf(desc, "---------   new hand count is 3 more");
        testResult(testG.handCount[p]+3, G.handCount[p], desc);
        sprintf(desc, "----------- new deck count is 3 less");
        testResult(testG.deckCount[p]-4, G.deckCount[p], desc);
        sprintf(desc, "--------- new played count is 1 more");
        testResult(testG.playedCardCount+1, G.playedCardCount, desc);

        for (j = 0; j < g; j++) {
            if (j != p) {
                G.whoseTurn = j;
                testG.whoseTurn = j;
                sprintf(desc, "--- player %d should have 1 more card", j+1);
                testResult(testG.handCount[j]+1, G.handCount[j], desc);
            }
        }
    }


    printf("\n\n ***** %s TESTS: PASSED %d OUT OF %d TESTS ***** \n\n", TESTCARD, numPass, numPass+numFail);
	return 0;
}
