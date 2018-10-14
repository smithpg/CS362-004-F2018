#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int adventurerEffect(struct gameState *state, int currentPlayer)
{
    int temphand[MAX_HAND]; // moved above the if statement
    int drawntreasure = 0;
    int cardDrawn;
    int z = 0; // this is the counter for the temp hand

    while (drawntreasure < 2)
    {

        //

        // if (state->deckCount[currentPlayer] < 1)
        // { //if the deck is empty we need to shuffle discard and add to deck
        //     shuffle(currentPlayer, state);
        // }

        drawCard(currentPlayer, state);
        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else
        {
            temphand[z] = cardDrawn;
            state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
            z++;
        }
    }
    while (z - 1 >= 0)
    {
        state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
        z = z - 1;
    }
    return 0;
}

int councilRoomEffect(struct gameState *state, int currentPlayer, int handPos)
{
    int i;
    //+4 Cards
    for (i = 0; i < 4; i++)
    {
        drawCard(currentPlayer, state);
    }

    //+1 Buy
    state->numBuys++;

    //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++)
    {
        // if (i != currentPlayer)
        // {
        drawCard(i, state);
        // }
    }

    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}

int gardensEffect() { return -1; }

int remodelEffect(struct gameState *state, int handPos, int currentPlayer, int choice1, int choice2)
{
    int i;
    int j = state->hand[currentPlayer][choice1]; //store card we will trash

    if ((getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2))
    {
        return -1;
    }

    gainCard(choice2, state, 0, currentPlayer);

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);

    //discard trashed card
    for (i = 0; i < state->handCount[currentPlayer]; i++)
    {
        if (state->hand[currentPlayer][i] == j)
        {
            discardCard(i, currentPlayer, state, 0);
            break;
        }
    }

    return 0;
}

int smithyEffect(struct gameState *state, int currentPlayer, int handPos)
{
    int i;
    //+3 Cards
    for (i = 1; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}
