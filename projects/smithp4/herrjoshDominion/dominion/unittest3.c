/* -----------------------------------------------------------------------
 * Unit Test for the drawCard function 
 * 
 * The intended behavior for this function is as follows: 
 
-	 if player's deck is non-empty, removes the top card from player's deck and adds it to their hand

-	 if player's deck is empty, shuffles discard contents into deck;

 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void myAssert(int condition)
{
    if (condition)
    {
        printf("\tPASSED\n");
    }
    else
    {
        printf("\tFAILED\n");
    }
}

int main()
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int handCount;
    int deckCount;
    int discardCount;
    int card;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING drawCard():\n");

    // initialize the game
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);

#if (NOISY_TEST == 1)
    printf("\nTest #1: Draw card from non-empty deck\n");
#endif
    card = G.deck[0][G.deckCount[0] - 1];
    deckCount = G.deckCount[0];
    handCount = G.handCount[0];

    drawCard(0, &G);

    myAssert(G.handCount[0] == handCount + 1 && G.deckCount[0] == deckCount - 1 && G.hand[0][handCount] == card);

#if (NOISY_TEST == 1)
    printf("\nTest #2: Draw card with empty deck\n");
#endif
    G.deckCount[0] = 0;
    G.discardCount[0] = 10;

    discardCount = G.discardCount[0];
    handCount = G.handCount[0];

    for (i = 0; i < 10; i++)
    {
        G.discard[0][i] = i;
    }

    drawCard(0, &G);

    myAssert(G.handCount[0] == handCount + 1 && G.deckCount[0] == discardCount - 1);

    return 0;
}