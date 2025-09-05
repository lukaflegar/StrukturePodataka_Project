#pragma once

#include "card.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NAME_LENGTH 51

struct _Player;
typedef struct _Player* PlayerPosition;

typedef struct _Player {
	char name[MAX_NAME_LENGTH];
	CardPosition firstCard;
	int remainingCards;

	PlayerPosition nextPlayer;
	PlayerPosition previousPlayer;
}Player;

PlayerPosition createPlayer(char* name); // Function to create a new player
int printPlayers(PlayerPosition player); // Function to print all players in a circular list
int printOnePlayer(PlayerPosition player); // Function to print a single player's details
int insertPlayerCircularList(PlayerPosition player, PlayerPosition newPlayer); // Function to insert a player into a circular list
int generatePlayerHand(PlayerPosition player); // Function to generate a player's hand
int deletePlayerFromList(PlayerPosition player); // Function to delete a player from a circular list
int deleteAllPlayers(PlayerPosition player); // Function to delete all players from a circular list
