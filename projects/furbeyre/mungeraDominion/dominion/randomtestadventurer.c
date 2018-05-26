/*
 * cardtest1.c -- ADVENTURER
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
#include <time.h>

#define TESTCARD "ADVENTURER"
int numPass = 0;
int numFail = 0;

int testResult(int exp, int act, char* desc) {
    printf("|  %-64s  ", desc);
    printf("|  Expected: %2d  |   Actual: %2d  |  Result:  ", exp, act);
    if (exp == act){
        printf("PASS  |\n");
        numPass++;
    } else {
        printf("FAIL  |\n");
        numFail++;
        return -1;
    }
    return 0;
}

int getNumTreasuresInHand(int currentPlayer, struct gameState* G) {
    int count = 0;
    int i, card;
    for ( i=0; i<G->handCount[currentPlayer]; i++) {
        card = G->hand[currentPlayer][i];
        if ( card == copper || card == silver || card == gold )
            count++;
    }
    return count;
}

void resetGame(int numPlayer, int* k, int seed, struct gameState* G) {
    memset(G, 0, sizeof(struct gameState));    // clear the game state
    initializeGame(numPlayer, k, seed, G);     // initialize a new game
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

// For testing purposes
void printHand(struct gameState* G) {
    int i;
    for ( i = 0; i < G->handCount[G->whoseTurn]; i++) {
        printf("Card %d: %d\n", i, G->hand[G->whoseTurn][i]);
    }
}

int main() {
    srand(time(NULL));
    int i, g, p, h, d, x, n;
    int oldTreasCount, newTreasCount;
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


    printf("\n************************************************ Random Testing ADVENTURER *************************************************\n");

    for (i = 1; i <= 500; i++) {
        g = getRandInt(2, 4);       // Get random number of players in game
        p = getRandInt(0, g-1);     // Get random player
        h = getRandInt(4, 9);      // Get random number of cards in hand
        d = getRandInt(10, 20);      // Get random number of cards in deck
        x = getRandInt(10, 20);      // Get random number of cards in deck
        n = getRandInt(0, h-1);       // Get random card position

        resetGame(g, k, seed, &G);
        G.whoseTurn = p;

        // Set hand
        G.handCount[p] = h;
        getRandCards(G.hand[p], h, pool, pool_len);
        G.hand[p][n] = adventurer;  // One of the cards in hand must be adventurer

        // Set deck
        G.deckCount[p] = d;
        getRandCards(G.deck[p], d, pool, pool_len);
        G.deck[p][getRandInt(0, 3)] = copper;  // Must be at least _ coppers in deck
        // G.deck[p][getRandInt(4, 7)] = copper;
        // G.deck[p][getRandInt(8, d)] = copper;

        // Set discard
        G.discardCount[p] = x;
        getRandCards(G.deck[p], x, pool, pool_len);
        G.discard[p][getRandInt(0, x)] = copper;  // Must be at least 1 copper in discard

        memcpy(&testG, &G, sizeof(struct gameState));       // Copy current game state

        cardEffect(adventurer, 0, 0, 0, &G, n, 0);

        printf("\n---------- Setup %d: %d Players, P%d, Hand Count %d, Card position %d, Deck Count %d, Discard Count %d ---------------\n", i, g, p+1, h, n, d, x);
        sprintf(desc, "---- new hand count is 2 more");
        if (testResult(testG.handCount[p]+2, G.handCount[p], desc) == -1 ) {
            printf("Hand Before: \n");
            printHand(&testG);
            printf("Hand After: \n");
            printHand(&G);
        }
        sprintf(desc, "---- new tresure count 2 more");
        oldTreasCount = getNumTreasuresInHand(p, &testG);
        newTreasCount = getNumTreasuresInHand(p, &G);
        if (testResult(oldTreasCount + 2, newTreasCount, desc) == -1 ) {
            printf("Hand Before: \n");
            printHand(&testG);
            printf("Hand After: \n");
            printHand(&G);
        }
    }

    printf("\n\n ***** %s TESTS: PASSED %d OUT OF %d TESTS ***** \n\n", TESTCARD, numPass, numPass+numFail);
	return 0;
}
