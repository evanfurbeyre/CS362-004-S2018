/*************************************************************************
*
* fullDeckCount() unit test
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
    int g, p, c, a, n, res;
    char desc[128];
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, steward};
    struct gameState G, testG;

    printf("\n******************************************* Testing fullDeckCount() Function ********************************************\n");

    printf("\n-------------------------------------- Test Game Conditions After Initialization ---------------------------------------\n");
    for (g = 2; g <= 4; g++) {
        for (p = 0; p < g; p++) {
            resetGame(g, k, seed, &G);
            res = fullDeckCount(p, 4, &G);
            sprintf(desc, "%d Players, Player %d Should Start With 7 coppers in their Deck", g, p+1);
            testResult(7, res, desc);
            res = fullDeckCount(p, 1, &G);
            sprintf(desc, "%d Players, Player %d Should Start With 3 estates in their Deck", g, p+1);
            testResult(3, res, desc);
        }
    }

    printf("\n-------------------------------------- Test Game Conditions After Gaining Cards ---------------------------------------\n");
    int cards[3] = {baron, steward, remodel};
    for (g = 2; g <= 4; g++) {      // For each possible number of players
        for (p = 0; p < g; p++) {       // For each player
            for (c = 0; c < 3; c++) {       // For 3 possible cards to add
                for (a = 0; a < 3; a++) {       // For adding each card up to 3 times
                    resetGame(g, k, seed, &G);
                    for (n = 0; n < a; n++) {
                        gainCard(cards[c], &G, n, p);  // Add Card to discard, deck, or hand
                    }
                    sprintf(desc, "%d Players, Player %d Should Have %d of card# %d in their Deck", g, p+1, a, c);
                    testResult(a, fullDeckCount(p, cards[c], &G), desc);
                }
            }
        }
    }

    printf("\n-------------------------------------- Test Game Conditions After Discard Cards ---------------------------------------\n");
    int hand[5] = {copper, estate, estate, copper, copper};
    for (g = 2; g <= 4; g++) {      // For each possible number of players
        for (p = 0; p < g; p++) {       // For each player
            resetGame(g, k, seed, &G);
            memcpy(G.hand[p], hand, sizeof(int) * 5);
            G.handCount[p] = 5;
            memcpy(&testG, &G, sizeof(struct gameState));
            discardCard(1, p, &G, 1);   // to trash
            discardCard(0, p, &G, 1);   // to trash
            sprintf(desc, "%d Players, Player %d Should Have 1 less copper in their Deck", g, p+1);
            testResult(fullDeckCount(p, copper, &testG)-1, fullDeckCount(p, copper, &G), desc);
            sprintf(desc, "%d Players, Player %d Should Have 1 less estate in their Deck", g, p+1);
            testResult(fullDeckCount(p, estate, &testG)-1, fullDeckCount(p, estate, &G), desc);
        }
    }



    return 0;
}
