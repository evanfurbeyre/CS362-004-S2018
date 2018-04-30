/*************************************************************************
*
* discardCard() unit test
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
    int i, g, p, h, d, n;
    int hc1, hc2, pc1, pc2;
    int trash;
    int seed = 1000;
    char desc[128];
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, steward};
    struct gameState G;
    int coppers[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
    }

    printf("\n********************************************* Testing discardCard() Function ********************************************\n");

    printf("\n------------------------------------------- Discard Card in 0 Position (No Trash) ---------------------------------------\n");
    resetGame(2, k, seed, &G);
    trash = 0;
    for (g = 2; g <= 4; g++) {  // For g number of players in game
        for (p = 0; p < 4; p++) {   // For player p in game
            for (h = 1; h <= 5; h++) {  // For n size of hand
                for (d = 1; d <= h; d++) { // For d number of consecutive discards
                    resetGame(g, k, seed, &G);
                    G.whoseTurn = p;
                    G.handCount[p] = h;
                    hc1 = numHandCards(&G);
                    pc1 = G.playedCardCount;
                    memcpy(G.hand[p], coppers, sizeof(int) * h);
                    hc1 = numHandCards(&G);
                    for (n = 0; n < d; n++) {
                        discardCard(0, p, &G, trash);
                    }
                    hc2 = numHandCards(&G);
                    pc2 = G.playedCardCount;
                    sprintf(desc, "%d Players, P%d, %d Card Hand,   Hand Count After Discarding %d Cards", g, p+1, h, d);
                    testResult(hc1-d , hc2, desc);
                    sprintf(desc, "%d Players, P%d, %d Card Hand, Played Count After Discarding %d Cards", g, p+1, h, d);
                    testResult(pc1+d, pc2, desc);
                }
            }
        }
    }

    printf("\n------------------------------------------- Discard Card in 0 Position (Trash It) ---------------------------------------\n");
    resetGame(2, k, seed, &G);
    trash = 1;
    for (g = 2; g <= 4; g++) {  // For g number of players in game
        for (p = 0; p < 4; p++) {   // For player p in game
            for (h = 1; h <= 5; h++) {  // For n size of hand
                for (d = 1; d <= h; d++) { // For d number of consecutive discards
                    resetGame(g, k, seed, &G);
                    G.whoseTurn = p;
                    G.handCount[p] = h;
                    hc1 = numHandCards(&G);
                    pc1 = G.playedCardCount;
                    memcpy(G.hand[p], coppers, sizeof(int) * h);
                    hc1 = numHandCards(&G);
                    for (n = 0; n < d; n++) {
                        discardCard(0, p, &G, trash);
                    }
                    hc2 = numHandCards(&G);
                    pc2 = G.playedCardCount;
                    sprintf(desc, "%d Players, P%d, %d Card Hand,   Hand Count After Trashing %d Cards", g, p+1, h, d);
                    testResult(hc1-d , hc2, desc);
                    sprintf(desc, "%d Players, P%d, %d Card Hand, Played Count After Trashing %d Cards", g, p+1, h, d);
                    testResult(pc1, pc2, desc);
                }
            }
        }
    }

    printf("\n------------------------------------------- Discard Card in last Position (No Trash) ---------------------------------------\n");
    resetGame(2, k, seed, &G);
    trash = 0;
    for (g = 2; g <= 4; g++) {  // For g number of players in game
        for (p = 0; p < 4; p++) {   // For player p in game
            for (h = 1; h <= 5; h++) {  // For h size of hand
                for (d = 1; d <= h; d++) { // For d number of consecutive discards
                    resetGame(g, k, seed, &G);
                    G.whoseTurn = p;
                    G.handCount[p] = h;
                    hc1 = numHandCards(&G);
                    pc1 = G.playedCardCount;
                    memcpy(G.hand[p], coppers, sizeof(int) * h);
                    hc1 = numHandCards(&G);
                    for (n = 0; n < d; n++) {
                        discardCard(h-1, p, &G, trash);
                    }
                    hc2 = numHandCards(&G);
                    pc2 = G.playedCardCount;
                    sprintf(desc, "%d Players, P%d, %d Card Hand,   Hand Count After Discarding %d Cards", g, p+1, h, d);
                    testResult(hc1-d , hc2, desc);
                    sprintf(desc, "%d Players, P%d, %d Card Hand, Played Count After Discarding %d Cards", g, p+1, h, d);
                    testResult(pc1+d, pc2, desc);
                }
            }
        }
    }

    printf("\n------------------------------------------- Discard Card in last Position (Trash It) ---------------------------------------\n");
    resetGame(2, k, seed, &G);
    trash = 1;
    for (g = 2; g <= 4; g++) {  // For g number of players in game
        for (p = 0; p < 4; p++) {   // For player p in game
            for (h = 1; h <= 5; h++) {  // For n size of hand
                for (d = 1; d <= h; d++) { // For d number of consecutive discards
                    resetGame(g, k, seed, &G);
                    G.whoseTurn = p;
                    G.handCount[p] = h;
                    hc1 = numHandCards(&G);
                    pc1 = G.playedCardCount;
                    memcpy(G.hand[p], coppers, sizeof(int) * h);
                    hc1 = numHandCards(&G);
                    for (n = 0; n < d; n++) {
                        discardCard(h-1, p, &G, trash);
                    }
                    hc2 = numHandCards(&G);
                    pc2 = G.playedCardCount;
                    sprintf(desc, "%d Players, P%d, %d Card Hand,   Hand Count After Trashing %d Cards", g, p+1, h, d);
                    testResult(hc1-d , hc2, desc);
                    sprintf(desc, "%d Players, P%d, %d Card Hand, Played Count After Trashing %d Cards", g, p+1, h, d);
                    testResult(pc1, pc2, desc);
                }
            }
        }
    }

    printf("\n------------------------------------------- Check card re-ordering functionality ---------------------------------------\n");
    resetGame(4, k, seed, &G);
    int hand1[5] = {copper, estate, smithy, silver, adventurer};
    int hand2[5] = {adventurer, estate, smithy, silver};
    memcpy(G.hand[0], hand1, sizeof(int) * 5);
    discardCard(0, 0, &G, 0);
    testResult(4, G.handCount[0], "Hand Length After Removing Card 1 Is Correct");
    for (i = 0; i < 4; i++) {
        sprintf(desc, "Card in hand position %d is correct", i);
        testResult(hand2[i], G.hand[0][i], desc);
    }

    resetGame(4, k, seed, &G);
    int hand3[5] = {copper, estate, smithy, silver, adventurer};
    int hand4[5] = {copper, estate, adventurer, silver};
    memcpy(G.hand[0], hand3, sizeof(int) * 5);
    discardCard(2, 0, &G, 0);
    testResult(4, G.handCount[0], "Hand Length After Removing Card 3 Is Correct");
    for (i = 0; i < 4; i++) {
        sprintf(desc, "Card in hand position %d is correct", i);
        testResult(hand4[i], G.hand[0][i], desc);
    }

    resetGame(4, k, seed, &G);
    int hand5[5] = {copper, estate, smithy, silver, adventurer};
    int hand6[5] = {copper, estate, smithy, silver};
    memcpy(G.hand[0], hand5, sizeof(int) * 5);
    discardCard(4, 0, &G, 0);
    testResult(4, G.handCount[0], "Hand Length After Removing Card 5 Is Correct");
    for (i = 0; i < 4; i++) {
        sprintf(desc, "Card in hand position %d is correct", i);
        testResult(hand6[i], G.hand[0][i], desc);
    }

    return 0;
}
