#define _CRT_SECURE_NO_WARNINGS
#include "player.h"

PlayerPosition createPlayer(char* name) {

    PlayerPosition player = NULL;
    player = (PlayerPosition)malloc(sizeof(Player));
    if (player == NULL) {
        printf("Memory allocation for player failed");
        return FAILED_MEMORY_ALLOCATION;
    }

    strcpy(player->name, name);
    player->remainingCards = 7;
    player->previousPlayer = player;
    player->nextPlayer = player;

    generatePlayerHand(player);
    return player;
}

int generatePlayerHand(PlayerPosition player) {
    player->firstCard = createCard();
    for (int i = 0; i < player->remainingCards - 1; i++) {
        CardPosition newCard = createCard();
        insertCardToList(player->firstCard, newCard);
    }
    return 0;
}

int printPlayers(PlayerPosition player) {
    PlayerPosition temp = player;
    do {
        printOnePlayer(temp);
        temp = temp->nextPlayer;
    } while (temp != NULL && temp != player);

    return 0;
}

int printOnePlayer(PlayerPosition player) {
    printf("Player's name: %s\n", player->name);
    printf("Number of remaining cards: %d\n", player->remainingCards);

    printCards(player->firstCard);
    return 0;
}

int insertPlayerCircularList(PlayerPosition player, PlayerPosition newPlayer) {
    PlayerPosition temp = player->previousPlayer;


    while (temp->nextPlayer != player) {
        temp = temp->nextPlayer;
    }

    temp->nextPlayer = newPlayer;
    newPlayer->nextPlayer = player;
    player->previousPlayer = newPlayer;
    newPlayer->previousPlayer = temp;

    return 0;
}

int deletePlayerFromList(PlayerPosition player) {
    if (player == NULL) return 0;

    if (player->nextPlayer == player && player->previousPlayer == player) {

        freeEntireList(player->firstCard);
        free(player);
        return 0;
    }

    PlayerPosition tempPrev = player->previousPlayer;
    PlayerPosition tempNext = player->nextPlayer;

    tempPrev->nextPlayer = tempNext;
    tempNext->previousPlayer = tempPrev;

    freeEntireList(player->firstCard);
    free(player);

    return 0;
}

int deleteAllPlayers(PlayerPosition player) {
    if (player == NULL) return 0;

    PlayerPosition temp = player->nextPlayer;

    while (temp != player) {
        PlayerPosition next = temp->nextPlayer;
        freeEntireList(temp->firstCard);
        free(temp);
        temp = next;
    }

    freeEntireList(player->firstCard);
    free(player);

    return 0;
}

