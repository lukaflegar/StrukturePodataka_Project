#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

GamePosition createGame() {
	GamePosition game = NULL;
	game = (GamePosition)malloc(sizeof(Game));
	if (game == NULL) {
		printf("Memory allocation for game failed\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	game->remainingPlayers = 0;
	game->topCard = createCard();
	game->currentPlayer = NULL;
	game->gameDirection = CLOCKWISE;

	return game;
}

int nextTurn(GamePosition game) {
	if (game->gameDirection == CLOCKWISE) {
		game->currentPlayer = game->currentPlayer->nextPlayer;
	}
	else {
		game->currentPlayer = game->currentPlayer->previousPlayer;
	}
	return 0;
}

int changeGameDirection(GamePosition game) {
	if (game->gameDirection == CLOCKWISE) {
		game->gameDirection = COUNTER_CLOCKWISE;
		printf("\nPlayer %s has changed the direction to COUNTER_CLOCKWISE!\n", game->currentPlayer->name);
	}
	else {
		game->gameDirection = CLOCKWISE;
		printf("\nPlayer %s has changed the direction to CLOCKWISE!\n", game->currentPlayer->name);
	}
	return 0;
}

int skipTurn(GamePosition game) {
	if (game->gameDirection == CLOCKWISE) {
		printf("\nPlayer %s has skipped player %s!\n", game->currentPlayer->name, game->currentPlayer->nextPlayer->name);
		game->currentPlayer = game->currentPlayer->nextPlayer->nextPlayer;
	}

	else {
		printf("\nPlayer %s has skipped player %s!\n", game->currentPlayer->name, game->currentPlayer->previousPlayer->name);
		game->currentPlayer = game->currentPlayer->previousPlayer->previousPlayer;
	}

	return 0;
}

int plusTwo(GamePosition game) {

	if (game->gameDirection == CLOCKWISE) {

		for (int i = 0; i < 2; i++) {
			CardPosition newCard = createCard();
			insertCardToList(game->currentPlayer->nextPlayer->firstCard, newCard);
			
			game->currentPlayer->nextPlayer->remainingCards++;
		}
		printf("\nPlayer %s drew 2 cards!\n", game->currentPlayer->nextPlayer->name);
	}

	if (game->gameDirection == COUNTER_CLOCKWISE) {

		for (int i = 0; i < 2; i++) {
			CardPosition newCard = createCard();
			insertCardToList(game->currentPlayer->previousPlayer->firstCard, newCard);
			
			game->currentPlayer->previousPlayer->remainingCards++;
		}
		printf("\nPlayer %s drew 2 cards!\n", game->currentPlayer->previousPlayer->name);
	}

	return 0;
}

int deleteGame(GamePosition game) {
	deleteAllPlayers(game->currentPlayer);
	free(game->topCard);
	free(game);
	game = NULL;

	return 0;
}


int mainGame(GamePosition game) {

	printf("\nGame begins!!!\n");

	while (game->remainingPlayers > 1) {
		printf("\nThe last played card is: \n");
		printOneCard(game->topCard);
		printf("\nPlayer's turn: \n");
		printOnePlayer(game->currentPlayer);

		int numValid = printValidCards(game->currentPlayer->firstCard, game->topCard);
		if (numValid == 0) {
			printf("Player %s has no valid cards, drawing one and passing the turn\n", game->currentPlayer->name);
			CardPosition newCard = createCard();
			insertCardToList(game->currentPlayer->firstCard, newCard);

			game->currentPlayer->remainingCards++;

			printf("Player drew the following card:\n");
			printOneCard(newCard);

			nextTurn(game);
		}
		else {
			int selectedCard = -1;
			int validSelection = 0;
			PlayerPosition finishedPlayer = NULL;

			do {
				printf("Select one of the valid cards above\n");
				if (scanf("%d", &selectedCard) != 1) {
					printf("\nInvalid input. Please enter a valid number.\n");
					while (getchar() != '\n');
					validSelection = 0;
					printValidCards(game->currentPlayer->firstCard, game->topCard);
				}

				else if (selectedCard < 1 || selectedCard > game->currentPlayer->remainingCards) {
					printf("\nThe selected card is not in the range of available cards for this player, please try again\n");
					//printOnePlayer(game->currentPlayer);
					printValidCards(game->currentPlayer->firstCard, game->topCard);
				}

				else {
					PlayerPosition playerWhoPlayed = game->currentPlayer;
					CardPosition chosenCard = chooseCard(game->currentPlayer->firstCard, selectedCard);

					if (checkValidCard(chosenCard, game->topCard)) {
						validSelection = 1;

						game->topCard->cardType = chosenCard->cardType;
						game->topCard->number = chosenCard->number;
						game->topCard->color = chosenCard->color;

						PlayerPosition nextPlayer = (game->gameDirection == CLOCKWISE) ? playerWhoPlayed->nextPlayer : playerWhoPlayed->previousPlayer;

						int cardType = chosenCard->cardType;
						playerWhoPlayed->firstCard = deleteCardFromList(playerWhoPlayed->firstCard, selectedCard - 1);
						playerWhoPlayed->remainingCards--;

						if (playerWhoPlayed->remainingCards == 1) {
							printf("\nPlayer %s: UNO!\n", playerWhoPlayed->name);
						}

						switch (cardType) {
						case SKIP_CARD:
							skipTurn(game);
							break;
						case REVERSE_CARD:
							changeGameDirection(game);
							nextTurn(game);
							break;
						case PLUSTWO_CARD:
							plusTwo(game);
							nextTurn(game);
							break;
						default:
							nextTurn(game);
							break;
						}

						if (playerWhoPlayed->remainingCards == 0) {
							printf("\nPlayer %s has finished the game!\n", playerWhoPlayed->name);
							deletePlayerFromList(playerWhoPlayed);
							game->remainingPlayers--;

							if (game->remainingPlayers == 1) {
								printf("\nPlayer %s is the last player remaining and has lost the game!\n", game->currentPlayer->name);
								break;
							}

							printf("%d players remaining\n", game->remainingPlayers);
						}

					}

					else {
						printf("\nThe card you have chosen is not valid, please try again\n");
						//printOnePlayer(game->currentPlayer); 
						printValidCards(game->currentPlayer->firstCard, game->topCard);
					}


				}
			} while (validSelection != 1);
		}
	}

	printf("\nGame over...\n");

	return EXIT_SUCCESS;

}
