#define _CRT_SECURE_NO_WARNINGS
#include "card.h"

CardPosition createCard() {
    CardPosition card = NULL;
    card = (CardPosition)malloc(sizeof(Card));
    if (card == NULL) {
        printf("Memory allocation for card failed\n");
        return FAILED_MEMORY_ALLOCATION;
    }

    card->color = rand() % 4;
    card->number = rand() % 10;
    card->cardType = probabilityRand();
    card->nextCard = NULL;

    return card;
}

int probabilityRand() {
    int randValue = rand() % 100;  

    if (randValue < 40) {
        return 0;  
    }
    else if (randValue < 65) {
        return 1;  
    }
    else if (randValue < 90) {
        return 2;  
    }
    else {
        return 3; 
    }
}

int checkValidCard(CardPosition card, CardPosition topCardOnTable) {
    if (card->cardType != NORMAL_CARD || topCardOnTable->cardType != NORMAL_CARD) {
        if (card->color == topCardOnTable->color || card->cardType == topCardOnTable->cardType) {
            return VALID_CARD;
        }

        else {
            return INVALID_CARD;
        }
    }
    else {
        if (card->color == topCardOnTable->color || card->number == topCardOnTable->number) {
            return VALID_CARD;
        }

        else {
            return INVALID_CARD;
        }
    }

}

int printValidCards(CardPosition hand, CardPosition topCardOnTable) {
    CardPosition temp = hand;
    int searchIndex = 1;
    int numValid = 0;

    printf("\n");
    while (temp != NULL) {
        if (checkValidCard(temp, topCardOnTable)) {
            printf("%d ", searchIndex);
            numValid++;
        }
        searchIndex++;
        temp = temp->nextCard;

    }
    printf("\n");
    return numValid;
}

int printOneCard(CardPosition card) {
    char cardSymbol;

    if (card->cardType == NORMAL_CARD) {
        cardSymbol = '0' + card->number;
    }
    else if (card->cardType == SKIP_CARD) {
        cardSymbol = (char)SKIP_CARD_SYMBOL;
    }
    else if (card->cardType == REVERSE_CARD) {
        cardSymbol = (char)REVERSE_CARD_SYMBOL;
    }
    else if (card->cardType == PLUSTWO_CARD) {
        cardSymbol = (char)PLUSTWO_CARD_SYMBOL;
    }

    else {
        printf("Invalid card type. Exiting the game.\n");
        exit(EXIT_FAILURE);
    }


    if (card->color == BLUE_COLOR) {
        printf(ANSI_COLOR_BLUE "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_BLUE "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardSymbol, VERTICAL_LINE);
        printf(ANSI_COLOR_BLUE "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else if (card->color == RED_COLOR) {
        printf(ANSI_COLOR_RED "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_RED "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardSymbol, VERTICAL_LINE);
        printf(ANSI_COLOR_RED "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else if (card->color == YELLOW_COLOR) {
        printf(ANSI_COLOR_YELLOW "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_YELLOW "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardSymbol, VERTICAL_LINE);
        printf(ANSI_COLOR_YELLOW "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else if (card->color == GREEN_COLOR) {
        printf(ANSI_COLOR_GREEN "%c%c%c" ANSI_COLOR_RESET "\n", TOP_LEFT_CORNER, HORIZONTAL_LINE, TOP_RIGHT_CORNER);
        printf(ANSI_COLOR_GREEN "%c%c%c" ANSI_COLOR_RESET "\n", VERTICAL_LINE, cardSymbol, VERTICAL_LINE);
        printf(ANSI_COLOR_GREEN "%c%c%c" ANSI_COLOR_RESET "\n", BOTTOM_LEFT_CORNER, HORIZONTAL_LINE, BOTTOM_RIGHT_CORNER);
    }
    else {
        printf("Invalid card color. Exiting the game.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int insertCardToList(CardPosition card, CardPosition newCard) {
    CardPosition temp = card;
    while (temp->nextCard != NULL) {
        temp = temp->nextCard;
    }

    temp->nextCard = newCard;

    return 0;
}

int printCards(CardPosition card) {
    CardPosition temp = card;
    int cardIndex = 1;

    do {
        printf("Card %d: \n", cardIndex);
        printOneCard(temp);
        temp = temp->nextCard;
        cardIndex++;
    } while (temp != NULL);

    return 0;
}

CardPosition chooseCard(CardPosition card, int index) {
    CardPosition temp = card;
    int searchIndex = 1;

    while (temp != NULL && searchIndex != index) {
        searchIndex++;
        temp = temp->nextCard;
    }

    if (temp == NULL) {
        printf("Error: Card not found at the given index.\n");
    }
    return temp;
}


int freeEntireList(CardPosition card) {
    CardPosition temp;
    while (card != NULL) {
        temp = card;
        card = card->nextCard;
        free(temp);
    }

    return 0;
}

int freeCardList(CardPosition card, CardPosition previous) {
    if (previous != NULL && card->nextCard != NULL) {
        previous->nextCard = card->nextCard;
    }
    free(card);

    return 0;
}

CardPosition deleteCardFromList(CardPosition card, int index) {
    if (card == NULL) {
        printf("Error: List is empty.\n");
        return NULL;
    }

    else if (index == 0) {
        CardPosition startList = card->nextCard;

        free(card);
        return startList;
    }

    else {
        int i = 0;
        CardPosition temp = card;
        CardPosition previous = card;
        while (i < index) {
            previous = temp;
            temp = temp->nextCard;
            i++;
        }

        if (temp == NULL) {
            printf("An error occurred while trying to delete a card. Exiting.\n");
            return card;
        }

        else {
            previous->nextCard = temp->nextCard;
            free(temp);
        }

        return card;
    }
}