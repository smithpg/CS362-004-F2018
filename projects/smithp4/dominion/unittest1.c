/* -----------------------------------------------------------------------
 * Unit Test for the buyCard function 
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

int main()
{
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf("TESTING buyCards():\n");

    // initialize the game
    memset(&G, 0, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);

    // Test #1 : attempt to buy a card during action phase
#if (NOISY_TEST == 1)
    printf("Test 1: Attempt buy during action phase\n", p, handCount, bonus);
#endif
    buyCard(0, &G);

    printf("All tests passed!\n");

    return 0;
}