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

// // For testing purposes
// void printHand(int player, struct gameState* G) {
//     int i;
//     for ( i = 0; i < G->handCount[player]; i++) {
//         printf("Card %d: %d\n", i, G->hand[player][i]);
//     }
// }

void resetGame(int numPlayer, int* k, int seed, struct gameState* G) {
    memset(G, 0, sizeof(struct gameState));    // clear the game state
    initializeGame(numPlayer, k, seed, G);     // initialize a new game
}

int main() {
    int g, p, n, c1, c2; // Loop Counters
    int res;    // result variable
    char desc[128];
    int seed = 1000;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    printf("\n****************************************************** Testing MINE *************************************************\n");

    printf("\n------------------------------------------------ Basic Before / After Tests (Copper) -----------------------------------------------\n");
    int startHand[5] = {copper, estate, copper, estate, copper};
    for (g = 2; g <= 4; g++) {      // for each possible number of players in the game
        for (p = 0; p < g; p++) {       // for each player in the game
            for (n = 0; n < 5; n++) {       // for each potential position of card in hand
                resetGame(g, k, seed, &G);
                G.whoseTurn = p;
                memcpy(G.hand[p], startHand, sizeof(int)*5);
                G.handCount[p] = 5;
                G.hand[p][n] = mine;
                memcpy(&testG, &G, sizeof(struct gameState));
                int trashCardIdx = getFirst(copper, p, &G);
                int newCard = G.hand[p][trashCardIdx]+1;
                res = cardEffect(mine, trashCardIdx, newCard , 0, &G, n, 0);
                sprintf(desc, "%d Players, P%d, Card position %d, total handCost correctly decreased by 2", g, p+1, n);
                testResult(getHandCost(p, &testG), getHandCost(p, &G)+2, desc);
                sprintf(desc, "%d Players, P%d, Card position %d,              new hand count is one less", g, p+1, n);
                testResult(testG.handCount[p]-1, G.handCount[p], desc);
            }
        }
    }

    printf("\n------------------------------------------------ Basic Before / After Tests (Silver) -----------------------------------------------\n");
    int startHand2[5] = {silver, estate, copper, silver, silver};
    for (g = 2; g <= 4; g++) {      // for each possible number of players in the game
        for (p = 0; p < g; p++) {       // for each player in the game
            for (n = 0; n < 5; n++) {       // for each potential position of card in hand
                resetGame(g, k, seed, &G);
                G.whoseTurn = p;
                memcpy(G.hand[p], startHand2, sizeof(int)*5);
                G.handCount[p] = 5;
                G.hand[p][n] = mine;
                memcpy(&testG, &G, sizeof(struct gameState));
                int trashCardIdx = getFirst(silver, p, &G);
                int newCard = G.hand[p][trashCardIdx]+1;
                res = cardEffect(mine, trashCardIdx, newCard , 0, &G, n, 0);
                sprintf(desc, "%d Players, P%d, Card position %d, total handCost correctly decreased by 2", g, p+1, n);
                testResult(getHandCost(p, &testG), getHandCost(p, &G)+2, desc);
                sprintf(desc, "%d Players, P%d, Card position %d,              new hand count is one less", g, p+1, n);
                testResult(testG.handCount[p]-1, G.handCount[p], desc);
            }
        }
    }

    printf("\n------------------------------------------------ Basic Before / After Tests (No Coppers or Silvers) -----------------------------------------------\n");
    int startHand3[5] = {smithy, estate, gardens, village, estate};
    for (g = 2; g <= 4; g++) {      // for each possible number of players in the game
        for (p = 0; p < g; p++) {       // for each player in the game
            for (n = 0; n < 5; n++) {       // for each potential position of card in hand
                resetGame(g, k, seed, &G);
                G.whoseTurn = p;
                memcpy(G.hand[p], startHand3, sizeof(int)*5);
                G.handCount[p] = 5;
                G.hand[p][n] = mine;
                memcpy(&testG, &G, sizeof(struct gameState));
                int trashCardIdx = getFirst(copper, p, &G);
                if (trashCardIdx == -1)
                    trashCardIdx = getFirst(silver, p, &G);
                int newCard = G.hand[p][trashCardIdx]+1;
                res = cardEffect(mine, trashCardIdx, newCard , 0, &G, n, 0);
                sprintf(desc, "%d Players, P%d, Card position %d, total handCost is the same", g, p+1, n);
                testResult(getHandCost(p, &testG), getHandCost(p, &G), desc);
                sprintf(desc, "%d Players, P%d, Card position %d, new hand count is the same", g, p+1, n);
                testResult(testG.handCount[p], G.handCount[p], desc);
            }
        }
    }

    printf("\n------------------------------------------------ Testing Junk Input Arguments For cardEffect/mineEffect -----------------------------------------------\n");
    resetGame(2, k, seed, &G);
    for (c1 = 0; c1 <= treasure_map; c1++) {
        if (c1 >= copper && c1 <= gold) // Skip copper, silver, gold
            c1 = gold+1;
        for (c2 = 0; c2 <= treasure_map; c2++) {
            G.hand[0][0] = c1;   // c1 is accessed via index, so we pass 0 into c1 parameter to get c1 card
            res = mineEffect( 0, c2 , 0, 0, &G);
            testResult(-1, res, "Passing Bad Input into cardEffect + mineEffect trash selection");
        }
    }

    resetGame(2, k, seed, &G);
    for (c1 = copper; c1 <= gold; c1++) {
        for (c2 = 0; c2 <= treasure_map; c2++) {
            if (c2 >= copper && c2 <= gold)
                c2 = gold+1;
            G.hand[0][0] = c1;   // c1 is accessed via index, so we pass 0 into c1 parameter to get c1 card
            res = mineEffect( 0, c2 , 0, 0, &G);
            testResult(-1, res, "Selecting Invalid Replacement Card After Trashing Copper or Silver");
        }
    }

    printf("\n------------------------------------------ You can trade a treasure card for a treasure card of equal or lower value -----------------------------------------------\n");
    resetGame(2, k, seed, &G);
    for (c1 = copper; c1 <= gold; c1++) {
        for (c2 = copper; c2 <= c1; c2++) {
            G.hand[0][0] = c1;   // c1 is accessed via index, so we pass 0 into c1 parameter to get c1 card
            // printf("G.hand[0][0]: %d\n", G.hand[0][0]);
            // printf("c2: %d\n", c2);
            res = mineEffect( 0, c2 , 0, 0, &G);
            testResult(0, res, "Should get mineEffect result 0 for trading in treasure card of equal or lower value");
        }
    }

    printf("\n---------------------------------------- Should Be Able To Trade Treasure Card for 1 Higher Treasure Card -----------------------------------------------\n");
    resetGame(2, k, seed, &G);
    G.whoseTurn = 0;
    for (c1 = copper; c1 <= silver; c1++) {
        c2 = c1+1;
        G.hand[0][0] = c1;   // c1 is accessed via index, so we pass 0 into c1 parameter to get c1 card
        res = mineEffect( 0, c2 , 0, 0, &G);
        testResult(0, res, "Trade Copper for Silver or Trade Silver for Gold");
    }

    printf("\n---------------------------------------- Should Not Be Able to Trade Treasure For Action  -----------------------------------------------\n");
    resetGame(2, k, seed, &G);
    G.hand[0][0] = gold;   // c1 is accessed via index, so we pass 0 into c1 parameter to get c1 card
    c2 = province;
    res = mineEffect( 0, c2 , 0, 0, &G);
    testResult(-1, res, "Should not be able to trade a gold for a province");

    printf("\n\n ***** %s TESTS: PASSED %d OUT OF %d TESTS ***** \n\n", TESTCARD, numPass, numPass+numFail);
	return 0;
}
