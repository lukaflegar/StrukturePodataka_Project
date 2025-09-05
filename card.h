#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define TOP_LEFT_CORNER 201
#define TOP_RIGHT_CORNER 187
#define BOTTOM_LEFT_CORNER 200
#define BOTTOM_RIGHT_CORNER 188
#define VERTICAL_LINE 186
#define HORIZONTAL_LINE 205

#define SKIP_CARD_SYMBOL 175
#define REVERSE_CARD_SYMBOL 47
#define PLUSTWO_CARD_SYMBOL 43

#define BLUE_COLOR 0
#define RED_COLOR 1
#define YELLOW_COLOR 2
#define GREEN_COLOR 3

#define NORMAL_CARD 0
#define SKIP_CARD 1
#define REVERSE_CARD 2
#define PLUSTWO_CARD 3

#define VALID_CARD 1
#define INVALID_CARD 0

#define FAILED_MEMORY_ALLOCATION (NULL)

struct _Card;
typedef struct _Card* CardPosition;

typedef struct _Card {
	int number;		
	int color;		
	int cardType;	

	CardPosition nextCard;
}Card;

CardPosition createCard(); // Function create a new UNO card
int probabilityRand(); // Function managing the card types
int checkValidCard(CardPosition card, CardPosition topCardOnTable); // Function check if a card is valid to play
CardPosition chooseCard(CardPosition card, int index); // Function choose a card from a player's hand based on index
int printCards(CardPosition card); // Function print all cards in a linked list
int printOneCard(CardPosition card); // Function print a single card
int printValidCards(CardPosition hand, CardPosition topCardOnTable); // Function print valid cards in a player's hand
int insertCardToList(CardPosition card, CardPosition newCard); // Function insert a card into a linked list
int freeEntireList(CardPosition card); // Functionfree memory of the entire card linked list
CardPosition deleteCardFromList(CardPosition card, int index); // Function delete a card from a linked list based on index
int freeCardList(CardPosition card, CardPosition previous); // Function free memory of a single card
