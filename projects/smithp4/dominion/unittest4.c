/* -----------------------------------------------------------------------
 * Unit Test for the discardCard function 
 * 
 * The intended behavior for this function is as follows: 
 
-	 if trash flag is not set, the card should be added to the discard 

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
    int j;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int handCount;
    int discardCount;
    int *handCopy;
    int discardIndex;

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING discardCard():\n");

    // initialize the game
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);

#if (NOISY_TEST == 1)
    printf("\nTest #1: Attempt to trash a card from player's hand\n");
#endif
    handCount = G.handCount[0];
    handCopy = malloc((G.handCount[0]) * sizeof(int));
    memcpy(handCopy, G.hand[0], (G.handCount[0]) * sizeof(int));

    discardCard(0, 0, &G, 1);

    myAssert(!memcmp(G.hand[0], handCopy + sizeof(int), G.handCount[0]));

#if (NOISY_TEST == 1)
    printf("\nTest #2: Attempt to discard (not trash) a card from player's hand\n");
#endif
    discardCount = G.discardCount[0];
    handCopy = malloc((G.handCount[0]) * sizeof(int));
    memcpy(handCopy, G.hand[0], (G.handCount[0]) * sizeof(int));

    discardCard(0, 0, &G, 0);

    myAssert(!memcmp(G.hand[0], handCopy + sizeof(int), G.handCount[0]) && G.discardCount[0] == discardCount + 1);

    return 0;
}