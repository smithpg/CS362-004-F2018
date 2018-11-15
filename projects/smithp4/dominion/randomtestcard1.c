
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
#define NUMTESTS 10

int getRandomCard()
{
    return floor(Random() * 27);
}

void randomizeCards(struct gameState *G)
{
    /*
    * This function randomizes the decks, discards, and hands 
    * for each player
    * 
    * NB: Assumes random stream has been init'd 
    */

    int i, j;

    G->numPlayers = floor(Random() * (MAX_PLAYERS - 2)) + 2;
    for (i = 0; i < G->numPlayers; i++)
    {
        G->deckCount[i] = floor(Random() * MAX_DECK);
        G->discardCount[i] = floor(Random() * MAX_DECK);
        G->handCount[i] = floor(Random() * MAX_HAND);

        for (j = 0; j < G->deckCount[i]; j++)
        {
            G->deck[i][j] = getRandomCard();
        }
        for (j = 0; j < G->discardCount[i]; j++)
        {
            G->discard[i][j] = getRandomCard();
        }
        for (j = 0; j < G->handCount[i]; j++)
        {
            G->hand[i][j] = getRandomCard();
        }
    }
}

int main()
{
    int newCards = 3;
    int discarded = 1;

    int i, j, m;
    int numTestsPassed = 0;
    int passCondition;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, remodel, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1 --------------
    initializeGame(numPlayers, k, seed, &G);
    for (i = 0; i < NUMTESTS; i++)
    {
        // randomize size and contents of deck, hand, discard
        randomizeCards(&G);
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

        passCondition = (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded) && (testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);

        if (passCondition)
            numTestsPassed++;
    }

    printf("\n >>>>> %i out of %i random tests passed <<<<<\n\n", numTestsPassed, NUMTESTS);

    return 0;
}
