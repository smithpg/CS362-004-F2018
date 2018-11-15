
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"
#define NUMTESTS 1000

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

void randomizeGameState(struct gameState *G)
{
    /*
    * This function randomizes the bytes of gameState argument, then
    * ensures deck discard and hand sizes are w/i allowed bounds for 
    * each player. 
    *
    * NB: Assumes random stream has been init'd 
    */

    int i, j;
    for (i = 0; i < sizeof(struct gameState); i++)
    {
        ((char *)G)[i] = floor(Random() * 256);
    }

    G->numPlayers = floor(Random() * (MAX_PLAYERS - 2)) + 2;
    printf("\nnumplaysers = %i\n", G->numPlayers);

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
    printf("exiting randomize fn");
}

int numEstatesInDiscard(int player, struct gameState *state)
{
    int i = 0, numEstates = 0;
    while (i < state->discardCount[player])
    {
        if (state->discard[player][i] == estate)
        {
            numEstates++;
        }

        i++;
    }

    return numEstates;
}

int numEstatesInHand(int player, struct gameState *state)
{
    int i, numEstates = 0;
    while (i < state->handCount[player])
    {
        if (state->hand[player][i] == estate)
        {
            numEstates++;
        }

        i++;
    }

    return numEstates;
}

int main()
{
    int i, j, m;
    struct gameState G, testG;

    int gainedCards = 0;
    int discarded = 1;
    int passCondition, origEstatesInHand, origEstatesInDiscard;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numTestsPassed = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int k[10] = {adventurer, remodel, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1 --------------
    printf("\nTEST 1: Choice = Gain Estate\n");
    initializeGame(numPlayers, k, seed, &G);
    for (i = 0; i < NUMTESTS; i++)
    {
        // randomize size and contents of deck, hand, discard
        randomizeCards(&G);
        origEstatesInDiscard = numEstatesInDiscard(thisPlayer, &G);

        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        choice1 = 0;
        gainedCards = 1;
        cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

        passCondition = (testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
        passCondition &= (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded + gainedCards);
        passCondition &= origEstatesInDiscard == numEstatesInDiscard(thisPlayer, &testG) - 1;
        passCondition &= testG.numBuys == 2;

        if (passCondition)
            numTestsPassed++;
    }
    printf("\n >>>>> %i out of %i random tests passed <<<<<\n\n", numTestsPassed, NUMTESTS);

    // ----------- TEST 2 --------------
    printf("\nTEST 2: Choice = Discard Estate for gold\n");
    for (i = 0; i < NUMTESTS; i++)
    {
        // randomize size and contents of deck, hand, discard
        randomizeCards(&G);
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));

        choice1 = 1;
        discarded = 2;

        m = floor(Random() * testG.handCount[0]);
        testG.hand[0][m] = estate;
        origEstatesInHand = numEstatesInHand(thisPlayer, &testG);

        cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

        passCondition = (testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
        passCondition &= (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
        passCondition &= origEstatesInHand == numEstatesInHand(thisPlayer, &testG) + 1;
        passCondition &= testG.numBuys == 2;

        if (passCondition)
            numTestsPassed++;
    }

    printf("\n >>>>> %i out of %i random tests passed <<<<<\n\n", numTestsPassed, NUMTESTS);

    return 0;
}
