/* -----------------------------------------------------------------------
 * Unit Test for the gainCard function 
 * 
 * The intended behavior for this function is as follows: 
 
-	 returns immediately without changing game state if the passed card enum is not available in supply

-	 adds gained card to discard if toFlag = 0

-	 adds gained card to deck if toFlag = 1

-	 adds gained card to hand if toFlag = 2 

-	 decrements supply pile for gained card

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
    memset(state->hand[state->whoseTurn], -1, MAX_HAND * sizeof(int));
    memset(state->deck[state->whoseTurn], -1, MAX_DECK * sizeof(int));

    state->discardCount[state->whoseTurn] = 0;
    state->handCount[state->whoseTurn] = 0;
    state->deckCount[state->whoseTurn] = 0;
}

int main()
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int supplyCount;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING gainCard():\n");

    // initialize the game
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);

#if (NOISY_TEST == 1)
    printf("\nTest #1: Attempt gain unavailable card from supply\n");
#endif
    setState(&G);
    gainCard(sea_hag, &G, 0, 0);
    myAssert(G.discardCount[0] == 0);

#if (NOISY_TEST == 1)
    printf("Test #2: Attempt to gain card to discard.\n");
#endif
    setState(&G);
    gainCard(adventurer, &G, 0, 0);
    myAssert(G.discardCount[0] != 0 && G.discard[0][0] == adventurer);

#if (NOISY_TEST == 1)
    printf("Test #3: Attempt to gain card to deck.\n");
#endif
    setState(&G);
    gainCard(adventurer, &G, 1, 0);
    myAssert(G.deckCount[0] != 0 && G.deck[0][0] == adventurer);

#if (NOISY_TEST == 1)
    printf("Test #4: Attempt to gain card to hand.\n");
#endif
    setState(&G);
    gainCard(adventurer, &G, 2, 0);
    myAssert(G.handCount[0] != 0 && G.hand[0][0] == adventurer);

#if (NOISY_TEST == 1)
    printf("Test #5: Check that supply pile is decremented after successful gain\n");
#endif
    setState(&G);
    supplyCount = G.supplyCount[adventurer];
    gainCard(adventurer, &G, 2, 0);
    myAssert(G.supplyCount[adventurer] == supplyCount - 1);

    return 0;
}