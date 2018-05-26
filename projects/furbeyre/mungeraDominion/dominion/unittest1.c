/*************************************************************************
*
* isGameOver() unit test
*
* Include the following line in your makefile:
* unittest1: unittest1.c dominion.o rngs.o
*      gcc -o unittest1.c -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testResult(int exp, int act, char* desc) {
    printf("|  %-64s  ", desc);
    printf("|  Expected: %d  |   Actual: %d  ", exp, act);
    if (exp == act){
        printf("|  Result:  PASS  |\n");
    } else {
        printf("|  Result:  FAIL  |\n");
    }
}

void resetGame(int numPlayer, int* k, int seed, struct gameState* G) {
    memset(G, 0, sizeof(struct gameState));    // clear the game state
    initializeGame(numPlayer, k, seed, G);     // initialize a new game
}

// For testing purposes
void printHand(struct gameState* G) {
    int i;
    for ( i = 0; i < G->handCount[G->whoseTurn]; i++) {
        printf("Card %d: %d\n", i, G->hand[G->whoseTurn][i]);
    }
}

int main() {
    int i, res;
    char testName[64];
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("\n******************************************* Testing isGameOver() Function ********************************************\n");

    printf("\n-------------------------------------- Testing Province Card Ending Conditions ---------------------------------------\n");
    resetGame(numPlayer, k, seed, &G);
    for (i = 10; i >= 1; i--) {
        G.supplyCount[province] = i;
        res = isGameOver(&G);
        sprintf(testName, "Province Card Supply Count is %2d:", G.supplyCount[province]);
        testResult(0, res, testName);
    }
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Province Card Supply Count is %2d:", G.supplyCount[province]);
    testResult(1, res, testName);

    printf("\n---------------------------------------- Testing Three Empty Supply Pile Conditions ----------------------------------\n");
    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[smithy] = 0;
    res = isGameOver(&G);
    sprintf(testName, "One Empty Pile (Smithy)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[copper] = 0;
    res = isGameOver(&G);
    sprintf(testName, "One Empty Pile (Copper)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[adventurer] = 0;
    G.supplyCount[silver] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Two Empty Piles (Silver and Adventurer)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 0;
    G.supplyCount[gardens] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Two Empty Piles (Estate and Gardens)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[silver] = 0;
    G.supplyCount[gold] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Two Empty Piles (Silver and Gold)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[estate] = 0;
    G.supplyCount[duchy] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Two Empty Piles (Estate and duchy)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[smithy] = 0;
    G.supplyCount[adventurer] = 0;
    G.supplyCount[feast] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Three Empty Piles (Smithy, Adventurer, Feast)");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[copper] = 0;
    G.supplyCount[silver] = 0;
    G.supplyCount[gold] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Three Empty Piles (Copper, Silver, Gold)");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[duchy] = 1;
    G.supplyCount[adventurer] = 1;
    G.supplyCount[feast] = 1;
    res = isGameOver(&G);
    sprintf(testName, "Three 1-Card Piles (duchy, Adventurer, Feast)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[smithy] = 1000000;
    G.supplyCount[adventurer] = 1000000;
    G.supplyCount[feast] = 1000000;
    res = isGameOver(&G);
    sprintf(testName, "Three 1000000-Card Piles (Smithy, Advent., Feast)");
    testResult(0, res, testName);

    resetGame(numPlayer, k, seed, &G);
    for (i = 0; i < 4; i++){
        G.supplyCount[k[i]] = 0;
    }
    res = isGameOver(&G);
    sprintf(testName, "Four Empty Card Piles (Advent, Council Room, Feast, Garden)");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    for (i = 0; i < 10; i++){
        G.supplyCount[k[i]] = 0;
    }
    res = isGameOver(&G);
    sprintf(testName, "All 10 Kingdom, Empty Card Piles");
    testResult(1, res, testName);

    printf("\n-------------------------------------- Testing Empty Piles/ Province Interactions ------------------------------------\n");
    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 0;
    G.supplyCount[gardens] = 0;
    res = isGameOver(&G);
    sprintf(testName, "One Empty Pile (gardens) and Empty Province");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[village] = 0;
    G.supplyCount[gardens] = 0;
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Two Empty Piles (gardens, village) and Empty Province");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[mine] = 0;
    G.supplyCount[gardens] = 0;
    G.supplyCount[village] = 0;
    res = isGameOver(&G);
    sprintf(testName, "Three Empty Piles (gardens, village, mine) and Empty Province");
    testResult(1, res, testName);

    printf("\n---------------------------------------------------- Testing Three Players -------------------------------------------\n");
    numPlayer = 3;

    resetGame(numPlayer, k, seed, &G);
    for (i = 3; i >= 1; i--) {
        G.supplyCount[province] = i;
        res = isGameOver(&G);
        sprintf(testName, "(3-player) Province Card Supply Count is %2d:", G.supplyCount[province]);
        testResult(0, res, testName);
    }

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(3-player) Province Card Supply Count is %2d:", G.supplyCount[province]);
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 0;
    G.supplyCount[gardens] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(3-player) One Empty Pile (gardens) and Empty Province");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[copper] = 0;
    G.supplyCount[estate] = 0;
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(3-player) Two Empty Piles(Copper, Estate) and Empty Province");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[curse] = 0;
    G.supplyCount[baron] = 0;
    G.supplyCount[great_hall] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(3-player) Three Empty Piles and Empty Province");
    testResult(1, res, testName);

    printf("\n---------------------------------------------------- Testing Four Players ---------------------------------------------\n");
    numPlayer = 4;

    resetGame(numPlayer, k, seed, &G);
    for (i = 3; i >= 1; i--) {
        G.supplyCount[province] = i;
        res = isGameOver(&G);
        sprintf(testName, "(4-player) Province Card Supply Count is %2d:", G.supplyCount[province]);
        testResult(0, res, testName);
    }

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(4-player) Province Card Supply Count is %2d:", G.supplyCount[province]);
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[province] = 0;
    G.supplyCount[remodel] = 0;
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(4-player) One Empty Pile (Remodel) and Empty Province");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[baron] = 0;
    G.supplyCount[great_hall] = 0;
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(4-player) Two Empty Piles and Empty Province");
    testResult(1, res, testName);

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[gold] = 0;
    G.supplyCount[curse] = 0;
    G.supplyCount[council_room] = 0;
    G.supplyCount[province] = 0;
    res = isGameOver(&G);
    sprintf(testName, "(4-player) Three Empty Piles and Empty Province");
    testResult(1, res, testName);

    printf("\n------------------------------------------------------ Strange Conditions --------------------------------------------\n");
    numPlayer = 2;

    resetGame(numPlayer, k, seed, &G);
    G.supplyCount[copper] = -1;
    res = isGameOver(&G);
    sprintf(testName, "Copper supply is -1");
    testResult(0, res, testName);

    printf("\n------------------------------------------------------ Buying Provinces (2Player) -----------------------------------------------\n");
    resetGame(2, k, seed, &G);
    assert(G.supplyCount[province] == 8);
    for (i = 0; i < 6; i++) {
        G.coins = 8;
        if (whoseTurn(&G) == 0)
            buyCard(province, &G);
        endTurn(&G);
    }
    res = isGameOver(&G);
    sprintf(testName, "Player 1 Buys Province for 6 Turns");
    testResult(0, res, testName);

    resetGame(2, k, seed, &G);
    assert(G.supplyCount[province] == 8);
    for (i = 0; i < 7; i++) {
        G.coins = 8;
        if (whoseTurn(&G) == 0)
            buyCard(province, &G);
        endTurn(&G);
    }
    res = isGameOver(&G);
    sprintf(testName, "Player 1 Buys Province for 7 Turns");
    testResult(0, res, testName);


    resetGame(2, k, seed, &G);
    assert(G.supplyCount[province] == 8);
    for (i = 0; i < 8; i++) {
        G.coins = 8;
        G.whoseTurn = 0;
        if (whoseTurn(&G) == 0) {
            buyCard(province, &G);
        }
        endTurn(&G);
    }
    res = isGameOver(&G);
    sprintf(testName, "Player 1 Buys Province for 8 Turns");
    testResult(1, res, testName);


    resetGame(2, k, seed, &G);
    assert(G.supplyCount[province] == 8);
    for (i = 0; i < 9; i++) {
        G.coins = 8;
        G.whoseTurn = 0;
        if (whoseTurn(&G) == 0)
            buyCard(province, &G);
        endTurn(&G);
    }
    res = isGameOver(&G);
    sprintf(testName, "Player 1 Buys Province for 9 Turns");
    testResult(1, res, testName);

    return 0;
}
