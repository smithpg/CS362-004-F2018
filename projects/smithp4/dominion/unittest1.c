/* -----------------------------------------------------------------------
 * Unit Test for the buyCard function 
 * 
 * The intended behavior for this function is as follows: 
 
-	 returns immediately without changing game state if it has been called during the wrong phase. 

-	 only allows a player to buy 1 card, or the number allowed by an action card played during the previous phase.

-	 does not add selected card to the player’s discard if there were none in the supply

-	 does not allow the player to buy a card they cannot afford

-    adds selected card to top of player's discard on successful buy

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

void setState(struct gameState *state)
{
    memset(state->discard[state->whoseTurn], -1, MAX_DECK * sizeof(int));
    state->discardCount[state->whoseTurn] = 0;

    state->supplyCount[adventurer] = 8;
    state->coins = 100;
    state->numBuys = 1;
}

int main()
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int discardCount;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf("TESTING buyCards():\n");

    // initialize the game
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);

#if (NOISY_TEST == 1)
    printf("\nTest #1: Attempt buy during action phase\n");
#endif
    setState(&G);
    discardCount = G.discardCount[0];
    buyCard(adventurer, &G);
    myAssert(discardCount == G.discardCount[0]);

#if (NOISY_TEST == 1)
    printf("Test #2: Attempt to buy more cards than should be allowed\n");
#endif
    setState(&G);
    discardCount = G.discardCount[0];
    G.numBuys = 3;
    G.coins = 100;
    for (i = 0; i < 4; i++)
    {
        buyCard(adventurer, &G);
    }
    myAssert(discardCount + 3 == G.discardCount[0]);

#if (NOISY_TEST == 1)
    printf("Test #3 : Attempt to buy a card that is out of stock\n");
#endif
    setState(&G);
    G.supplyCount[adventurer] = 0;
    buyCard(adventurer, &G);

    myAssert(G.discardCount[0] == 0);

#if (NOISY_TEST == 1)
    printf("Test #4 : Attempt to buy a card that player cannot afford\n");
#endif
    setState(&G);
    G.coins = 0;
    buyCard(adventurer, &G);
    myAssert(G.discardCount[0] == 0);

#if (NOISY_TEST == 1)
    printf("Test #5 : Check that selected card is added to top of discard on succesful purchase\n");
#endif
    setState(&G);
    buyCard(adventurer, &G);
    myAssert(G.discard[0][G.discardCount[0] - 1] == adventurer);

    return 0;
}