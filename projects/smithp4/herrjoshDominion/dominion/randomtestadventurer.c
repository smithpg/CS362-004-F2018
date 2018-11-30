
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define NUMTESTS 1000

int isTreasure(int card)
{
    return (card >= 4 && card <= 6);
}

int main()
{
    int newCards = 2;
    int discarded = 0;

    int randomCard;
    int treasureCounter;
    int deckLen;

    int i, j, randIndex;
    int testPassed;
    int numPassed = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, remodel, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    SelectStream(2);
    PutSeed(3);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1 --------------
    for (i = 0; i < NUMTESTS; i++)
    {
        deckLen = floor(Random() * (MAX_DECK - 20)) + 20;
        printf("%i", deckLen);
        G.deckCount[thisPlayer] = deckLen;

        for (j = 0; j < deckLen; j++)
        {
            randomCard = floor(Random() * 27);
            G.deck[thisPlayer][j] = randomCard;
        }
        // Ensure that random deck has at least 2 treasure cards
        randIndex = floor(Random() * deckLen);
        G.deck[thisPlayer][randIndex] = 6;
        G.deck[thisPlayer][(randIndex + 2) % deckLen] = 6;

        discarded = 0;
        treasureCounter = 0;
        j = deckLen - 1;
        while (1)
        {
            if (isTreasure(G.deck[thisPlayer][j]))
            {
                treasureCounter++;
                if (treasureCounter == 2)
                {
                    break;
                }
            }
            else
            {
                discarded++;
            }
            j--;
        }

        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

        testPassed = 1;

        if (!(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1))
        {
            testPassed = 0;
        }
        else if (!(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards - discarded))
        {
            testPassed = 0;
        }
        else if (!(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded))
        {
            testPassed = 0;
        }

        numPassed += testPassed;
    }

    printf("\n >>>>> Testing complete: %i/%i random tests passed<<<<<\n\n", numPassed, NUMTESTS);

    return 0;
}
