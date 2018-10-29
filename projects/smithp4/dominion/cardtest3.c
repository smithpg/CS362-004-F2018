
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "baron"
#define NUMTESTS 2

int didGainEstate(int player, struct gameState *state)
{
    int i = 0;
    while (i < state->discardCount[player])
    {
        if (state->discard[player][i] == estate)
        {
            return 1;
        }

        i++;
    }

    return 0;
}

int handContainsEstate(int player, struct gameState *state)
{
    int i;
    while (i < state->handCount[player])
    {
        if (state->hand[player][i] == estate)
        {
            return 1;
        }

        i++;
    }

    return 0;
}

void evaluateTestCondition(int *resultsArray, int testNumber, int condition)
{
    if (resultsArray[testNumber - 1] == 0)
    {
        return;
    }
    else
    {
        resultsArray[testNumber - 1] = condition;
    }
}

void printTestResults(int *resultsArray, int arrayLen)
{
    int i;

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    for (i = 0; i < arrayLen; i++)
    {
        if (resultsArray[i])
        {
            printf("\tTEST %i: PASSED\n", i + 1);
        }
        else
        {

            printf("\tTEST %i: FAILED\n", i + 1);
        }
    }
}

int main()
{

    int testResults[2] = {1, 1};

    int gainedCards = 0;
    int discarded = 1;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, remodel, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1 --------------
    printf("\nTEST 1: Choice = Gain Estate\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 0;
    gainedCards = 1;
    cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

    evaluateTestCondition(&testResults, 1, testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
    printf("\thand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);

    evaluateTestCondition(&testResults, 1, testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded + gainedCards);
    printf("\tdiscard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded + gainedCards);

    evaluateTestCondition(&testResults, 1, didGainEstate(thisPlayer, &testG));
    if (didGainEstate(thisPlayer, &testG))
    {
        printf("\tdiscard contains gained estate card\n");
    }
    else
        printf("\tdiscard does NOT contain an estate card\n");

    evaluateTestCondition(&testResults, 1, testG.numBuys == 2);
    printf("\tnumBuys = %i, expected 2\n", testG.numBuys);
    // ----------- TEST 2 --------------
    printf("\nTEST 2: Choice = Discard Estate for gold\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    choice1 = 1;
    discarded = 2;
    testG.hand[0][1] = estate;

    cardEffect(baron, choice1, choice2, choice3, &testG, handpos, &bonus);

    evaluateTestCondition(&testResults, 2, testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded);
    printf("\thand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);

    evaluateTestCondition(&testResults, 2, testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);
    printf("\tdiscard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);

    evaluateTestCondition(&testResults, 2, testG.numBuys == 2);
    printf("\tnumBuys = %i, expected 2\n", testG.numBuys);

    evaluateTestCondition(&testResults, 2, !handContainsEstate(thisPlayer, &testG));
    printf("\tplayer's hand no longer contains estate card\n", testG.numBuys);

    printTestResults(testResults, NUMTESTS);

    return 0;
}
