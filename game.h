#pragma once

#include "player.h"
#include <stdio.h>
#include <stdlib.h>

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

struct _Game;
typedef struct _Game* GamePosition;
typedef struct _Game {
	PlayerPosition currentPlayer;
	CardPosition topCard;
	int gameDirection;
	int remainingPlayers;

}Game;

GamePosition createGame();	// Function create a new game
int changeGameDirection(GamePosition game);  // Function change the game direction
int nextTurn(GamePosition game);  // Function move to the next turn
int skipTurn(GamePosition game);  // Function skip the next player's turn
int plusTwo(GamePosition game);   // Function add 2 more cards to next/previous player
int mainGame(GamePosition game);  // Function main game process implemented
int deleteGame(GamePosition game);  // Function delete the game
