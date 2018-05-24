/*************************************************************************
*
* numHandCars() unit test
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
    printf("|  Expected: %2d  |   Actual: %2d  ", exp, act);
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

int main() {
    int i, h, j, c, res, numHandCardsBefore;
    int seed = 1000;
    char desc[128];
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, steward};
    struct gameState G;
    int coppers[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
    }

    printf("\n******************************************* Testing numHandCards() Function ********************************************\n");

    printf("\n--------------------------------------- Basic Starting Hands After Initialization ---------------------------------------\n");
    resetGame(2, k, seed, &G);
    res = numHandCards(&G);
    assert(whoseTurn(&G) == 0);
    testResult(5, res, "Player 1 Should Start With 5 cards in their Hand");
    endTurn(&G);
    res = numHandCards(&G);
    assert(whoseTurn(&G) == 1);
    testResult(5, res, "Player 2 Should Start With 5 cards in their Hand");

    printf("\n------------------------------------------------------------ Effects of Gain Card ---------------------------------------\n");
    for (h = 2; h < 5; h++) {
        for (j = 0; j < h; j++) {
            for (c = 0; c <= 30; c++) {
                resetGame(h, k, seed, &G);
                G.handCount[j] = 5;
                memcpy(G.hand[j], coppers, sizeof(int) * G.handCount[j]);
                for (i = 0; i < c; i++){
                    gainCard(copper, &G, 2, j);
                }
                sprintf(desc, "%d Players, P%d Should Have %d Cards After Gaining %d Cards", h, j+1, 5+c, c);
                G.whoseTurn = j;
                res = numHandCards(&G);
                testResult(5+c, res, desc);
            }
        }
    }

    printf("\n---------------------------------------------------- Effects of Discard Card --------------------------------------------\n");
    for (h = 2; h < 5; h++) {
        for (j = 0; j < h; j++) {
            for (c = 1; c <= 5; c++) {
                resetGame(h, k, seed, &G);
                G.handCount[j] = 5;
                memcpy(G.hand[j], coppers, sizeof(int) * G.handCount[j]);
                for (i = 0; i < c; i++){
                    discardCard(0, j, &G, 0);
                }
                sprintf(desc, "%d Players, P%d Should Have %d Cards After Discarding %d Cards", h, j+1, 5-c, c);
                G.whoseTurn = j;
                res = numHandCards(&G);
                testResult(5-c, res, desc);
            }
        }
    }

    printf("\n--------------------------------------------------------- Smithy Effect -------------------------------------------------\n");
    resetGame(2, k, seed, &G);
    G.hand[0][0] = smithy;
    numHandCardsBefore = numHandCards(&G);
    smithyEffect(0, 0, &G);
    res = numHandCards(&G);
    testResult(7, res, "Player 1 Should Have 7 Cards In Hand After Playing Smithy");
    endTurn(&G);
    G.hand[1][0] = smithy;
    numHandCardsBefore = numHandCards(&G);
    smithyEffect(0, 1, &G);
    res = numHandCards(&G);
    testResult(7, res, "Player 2 Should Have 7 Cards In Hand After Playing Smithy");


    printf("\n-------------------------------------------------------- Council Room Effect --------------------------------------------\n");
    resetGame(2, k, seed, &G);
    G.hand[0][0] = council_room;
    numHandCardsBefore = numHandCards(&G);
    councilRoomEffect(0, 0, &G);
    res = numHandCards(&G);
    testResult(8, res, "Player 1 Should Have 8 Cards In (Active) Hand After Council Room");
    endTurn(&G);
    res = numHandCards(&G);
    testResult(6, res, "Player 2 Should Have 6 Cards In Hand After Player 1 plays C.R.");


    return 0;
}
