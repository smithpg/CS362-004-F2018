
#ifndef _CARDS_H
#define _CARDS_H

#include "dominion.h"

int adventurerEffect(struct gameState *state, int currentPlayer);
int councilRoomEffect(struct gameState *state, int currentPlayer, int handPos);
int gardensEffect();
int remodelEffect(struct gameState *state, int handPos, int currentPlayer, int choice1, int choice2);
int smithyEffect(struct gameState *state, int currentPlayer, int handPos);

#endif