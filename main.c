#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "game.h"
#include <crtdbg.h>

#define MENU_ADD_PLAYER 1
#define MENU_SHOW_PLAYERS 2
#define MENU_START_GAME 3
#define MENU_SHOW_GAME_RULES 4
#define MENU_QUIT_GAME 5
#define MENU_INVALID_SELECTION -1

int printGameRules();
int printMenu();
int printHeadlineFile(char* fileName);
int handleAddPlayer(GamePosition game);
int handleShowPlayers(GamePosition game);
int handleStartGame(GamePosition* game);
int handleQuitGame(GamePosition game);


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    srand((unsigned int)time(NULL));
    GamePosition game = NULL;
    game = createGame();

    printHeadlineFile("headline2.txt");

    int menuSelection = MENU_INVALID_SELECTION;

    while (menuSelection != MENU_QUIT_GAME) {
        do {
            printMenu();
            if (scanf("%d", &menuSelection) != 1) {
                printf("\nInvalid input. Please enter a number between 1 and 5.\n");
                while (getchar() != '\n'); 
                menuSelection = MENU_INVALID_SELECTION;
            }
            else if (menuSelection < MENU_ADD_PLAYER || menuSelection > MENU_QUIT_GAME) {
                printf("\nInvalid selection. Please select one of the following options (1-5):\n");
                menuSelection = MENU_INVALID_SELECTION;
            }
        } while (menuSelection == MENU_INVALID_SELECTION);

        switch (menuSelection) {
        case MENU_ADD_PLAYER:
            handleAddPlayer(game);
            break;

        case MENU_SHOW_PLAYERS:
            handleShowPlayers(game);
            break;

        case MENU_START_GAME:
            handleStartGame(&game);
            break;

        case MENU_SHOW_GAME_RULES:
            printGameRules();
            break;

        case MENU_QUIT_GAME:
            handleQuitGame(game);
            break;

        default:
            printf("Invalid selection. Please select one of the following options (1-5):\n");
            break;
        }
    }
    _CrtDumpMemoryLeaks();
    return EXIT_SUCCESS;
}

int printGameRules() {

    printf("\n=======================================\n");
    printf(ANSI_COLOR_GREEN"\tGame Rules\n"ANSI_COLOR_RESET);
    printf("=======================================\n");
    printf("1. Players take turns clockwise.\n");
    printf("2. On your turn, you can play a card of the same color, type or number as the card on top of the deck.\n");
    printf("3. Special cards have additional effects, skip turn (>>), reverse direction (/) or plus 2 cards to next player (+).\n");
    printf("4. You can only select one of your cards if it is valid. If you have no valid cards, you will automatically draw one.\n");
    printf("5. The winner is the player who successfully gets rid of all their cards before anyone else.\n");
    printf("=======================================\n\n");

    return 0;
}

int printMenu() {

    printf("\n=======================================\n");
    printf(ANSI_COLOR_RED"\tMenu\n"ANSI_COLOR_RESET);
    printf("=======================================\n");
    printf("1. Add a player\n");
    printf("2. Show list of players\n");
    printf("3. Start the game\n");
    printf("4. Show game rules\n");
    printf("5. Quit the game\n");
    printf("\nChoose number 1-5\n");
    printf("=======================================\n");

    return 0;
}

int printHeadlineFile(char* fileName) {
    FILE* file;
    char line[1024] = { 0 };

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error: File '%s' not found.\n", fileName);
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET, line);
    }

    fclose(file);

    return 0;
}

int handleAddPlayer(GamePosition game) {
    printf("\nEnter your name:\n");
    char* name = NULL;
    name = malloc(MAX_NAME_LENGTH * sizeof(char)); 
    if (name == NULL) {
        printf("Memory allocation error. Exiting.\n");
        exit(EXIT_FAILURE);
    }

    while (getchar() != '\n'); 
    if (fgets(name, MAX_NAME_LENGTH, stdin) == NULL) {
        printf("Error reading input. Please try again.\n");
        free(name);
        return 1;
    }

    name[strcspn(name, "\n")] = 0;

    if (strlen(name) == 0) {
        printf("Name cannot be empty. Please try again.\n");
        free(name);
        return 1;
    }

    for (int i = 0; name[i] != '\0'; i++) {
        if (isdigit(name[i])) {
            printf("Name can only contain letters. Please try again.\n");
            free(name);
            return 1;
        }
    }

    if (game->currentPlayer != NULL) {
        PlayerPosition temp = game->currentPlayer;
        do {
            if (strcmp(temp->name, name) == 0) {
                printf("Player with name '%s' already exists! Please choose a different name.\n", name);
                free(name);
                return 1; // prekid dodavanja
            }
            temp = temp->nextPlayer;
        } while (temp != game->currentPlayer);
    }

    if (game->currentPlayer == NULL) {
        game->currentPlayer = createPlayer(name);
    }
    else {
        PlayerPosition player = createPlayer(name);
        insertPlayerCircularList(game->currentPlayer, player);
    }

    game->remainingPlayers++;
    printf("Player '%s' added successfully!\n", name);

    free(name);

    return 0;
}

int handleShowPlayers(GamePosition game) {
    if (game->currentPlayer == NULL) {
        printf("\nThere are currently no players waiting for the game\n");
    }
    else {
        printPlayers(game->currentPlayer);
    }

    return 0;
}


int handleStartGame(GamePosition* gamePtr) {
    GamePosition game = *gamePtr;

    if (game->remainingPlayers >= 2) {
        mainGame(game);
		deleteGame(game);
		exit(EXIT_SUCCESS);
    }

    else {
        printf("\nThere are not enough players to start the game. Minimum of 2 players required.\n");
        printf("Please add more players to continue.\n");
    }

    return 0;
}

int handleQuitGame(GamePosition game) {
    printf("\nExiting the game. See you soon!\n");
    printf("Thank you for playing!\n");

    deleteGame(game);
    return 0;
}

