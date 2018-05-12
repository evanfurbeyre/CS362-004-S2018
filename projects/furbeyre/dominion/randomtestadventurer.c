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

void testResultCmpr(int exp, char* cmpr, int act, char* desc) {
    printf("|  %-64s  ", desc);
    printf("|  Expected: %2d  |   Actual: %2d  |  Result:  ", exp, act);
    if ( !strcmp(cmpr, ">=") && exp >= act ){
        printf("PASS  |\n");
        numPass++;
    } else if ( !strcmp(cmpr, ">=") && exp < act ) {
        printf("FAIL  |\n");
        numFail++;
    } else if ( !strcmp(cmpr, "<=") && exp <= act ) {
        printf("PASS  |\n");
        numPass++;
    } else if ( !strcmp(cmpr, "<=") && exp > act ) {
        printf("FAIL  |\n");
        numFail++;
    }
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
    return 2;
}

int main() {
    srand(time(NULL));
    int i, g, p, n;
    int oldTreasCount, newTreasCount;
    char desc[128];
    int seed = 1000;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf("\n****************************************************** Testing ADVENTURER *************************************************\n");

    printf("\n------------------------------------------------ Basic Before / After Tests -----------------------------------------------\n");
    // for (g = 2; g <= 4; g++) {      // for each possible number of players in the game
    //     for (p = 0; p < g; p++) {       // for each player in the game
    //         for (n = 0; n < 5; n++) {       // for each potential position of card in hand
    //             resetGame(g, k, seed, &G);
    //             memcpy(&testG, &G, sizeof(struct gameState));
    //             G.whoseTurn = p;
    //             cardEffect(adventurer, 0, 0, 0, &G, n, 0);
    //             sprintf(desc, "%d Players, P%d, Card position %d,  new hand count is at least 2 more", g, p+1, n);
    //             testResultCmpr(testG.handCount[p]+2, "<=", G.handCount[p], desc);
    //             sprintf(desc, "%d Players, P%d, Card position %d,  new deck count is at least 2 less", g, p+1, n);
    //             testResultCmpr(testG.deckCount[p]-2, ">=", G.deckCount[p], desc);
    //             sprintf(desc, "%d Players, P%d, Card position %d, new treasure count at least 2 more", g, p+1, n);
    //             oldTreasCount = getNumTreasuresInHand(p, &testG);
    //             newTreasCount = getNumTreasuresInHand(p, &G);
    //             testResultCmpr(oldTreasCount + 2, "<=", newTreasCount, desc);
    //         }
    //     }
    // }

    for (i = 0; i < 10; i++) {
        g = getRandInt(2, 4);
        p = getRandInt(0, g-1);
        n = getRandInt(0, 5);
        resetGame(g, k, seed, &G);
        memcpy(&testG, &G, sizeof(struct gameState));
        G.whoseTurn = p;
        cardEffect(adventurer, 0, 0, 0, &G, n, 0);
        // sprintf(desc, "%d Players, P%d, Card position %d,  new hand count is at least 2 more", g, p+1, n);
        // testResultCmpr(testG.handCount[p]+2, "<=", G.handCount[p], desc);
        // sprintf(desc, "%d Players, P%d, Card position %d,  new deck count is at least 2 less", g, p+1, n);
        // testResultCmpr(testG.deckCount[p]-2, ">=", G.deckCount[p], desc);
        // sprintf(desc, "%d Players, P%d, Card position %d, new treasure count at least 2 more", g, p+1, n);
        // oldTreasCount = getNumTreasuresInHand(p, &testG);
        // newTreasCount = getNumTreasuresInHand(p, &G);
        // testResultCmpr(oldTreasCount + 2, "<=", newTreasCount, desc);
    }

    // printf("\n-------------------------------------------- Hand Content And Card Positioning --------------------------------------------\n");
    // int handPos;
    //
    // resetGame(4, k, seed, &G);
    // printf("--- Hand Before Playing Adventurer:           adventurer ---\n");
    // printf("--- Deck Before Playing Adventurer:           gold, copper ---\n");
    // printf("--- Hand After Playing Adventurer Should be:  copper, gold ---\n");
    // int hand1[1] = {adventurer};
    // int deck1[2] = {gold, copper};
    // memcpy(G.hand[0], hand1, sizeof(int) * 1);  // Copy defined hand into player 0 hand
    // memcpy(G.deck[0], deck1, sizeof(int) * 2);  // Copy defined deck into player 0 deck
    // G.handCount[0] = 1;
    // G.deckCount[0] = 2;
    // G.whoseTurn = 0;
    // handPos = 0;
    // cardEffect(adventurer, 0, 0, 0, &G, handPos, 0);
    // testResult(2, G.handCount[0], "Hand Count Should be 2");
    // testResult(copper, handCard(0, &G), "Card in position 0 should be copper");
    // testResult(gold, handCard(1, &G), "Card in position 1 should be gold");
    //
    //
    // resetGame(4, k, seed, &G);
    // printf("\n--- Hand Before Playing Adventurer:           copper, estate, smithy, silver, adventurer ---\n");
    // printf("--- Deck Before Playing Adventurer:           estate, smithy, estate, gold, copper ---\n");
    // printf("--- Hand After Playing Adventurer Should be:  copper, estate, smithy, silver, copper, gold ---\n");
    // int hand2[5] = {copper, estate, smithy, silver, adventurer};
    // int deck2[5] = {estate, smithy, estate, gold, copper};
    // memcpy(G.hand[0], hand2, sizeof(int) * 5);  // Copy defined hand into player 0 hand
    // memcpy(G.deck[0], deck2, sizeof(int) * 5);  // Copy defined deck into player 0 deck
    // G.handCount[0] = 5;
    // G.deckCount[0] = 5;
    // G.whoseTurn = 0;
    // handPos = 4;
    // cardEffect(adventurer, 0, 0, 0, &G, handPos, 0);
    // testResult(6, G.handCount[0], "Hand Count Should be 7");
    // testResult(copper, handCard(0, &G), "Card in position 0 should be copper");
    // testResult(estate, handCard(1, &G), "Card in position 1 should be estate");
    // testResult(smithy, handCard(1, &G), "Card in position 2 should be smithy");
    // testResult(silver, handCard(3, &G), "Card in position 3 should be silver");
    // testResult(  gold, handCard(4, &G), "Card in position 4 should be gold");
    // testResult(copper, handCard(5, &G), "Card in position 5 should be copper");



    printf("\n\n ***** %s TESTS: PASSED %d OUT OF %d TESTS ***** \n\n", TESTCARD, numPass, numPass+numFail);
	return 0;
}
