#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#include"bingo.h"

#define ROW 3
#define COLUMN 10
#define EMPTY_SPACE 4
#define MAX_DRAWN 90

int players, player, row, col, disp, draw_index, draw_cnt;
int *drawn_card, ***cards, ***empty_space;
char empty = '*';
char checked = 'C';
char file_name[] = "bingo.sav";
//FILE *filep;

void get_start_main_menu() {
	printf("[*: empty, C: drawn number]\n");
	get_main_menu();
}

void get_exit_menu() {
	// free dynamic memory
	// *need to free 3pointers! ont only one: cards and empty_space
	/*free(drawn_card);
	free(cards);
	free(empty_space);
	drawn_card = NULL;
	cards = NULL;
	empty_space = NULL;*/
	printf("\ndraw count is %d player is %d\n", draw_cnt, players);
	
	for (player = 0; player < players; player++) {
		for (row = 0; row < ROW; row++) {
			free(cards[player][row]);
			//free(empty_space[player][row]);
			cards[player][row] = NULL;
			//empty_space[player][row] = NULL;
		}
		free(cards[player]);
		//free(empty_space[player]);
		cards[player] = NULL;
		//empty_space[player] = NULL;
	}
	free(drawn_card);
	free(cards);
	//free(empty_space);
	drawn_card = NULL;
	cards = NULL;
	//empty_space = NULL;

	get_main_menu();
}

void generate_cards() {

	// declare and initialise variables
	int range, empty_index;
	srand(time(NULL));
	players = get_manager_menu();

	// allocate pointers
	drawn_card = (int*)malloc(MAX_DRAWN * sizeof(int));
	cards = (int***)malloc(players * sizeof(int**));
	empty_space = (int***)malloc(players * sizeof(int**));
	if (players == 1) {
		printf("\n%d player is ready!\n\n", players);
	}
	else {
		printf("\n%d players are ready!\n\n", players);
	}
	for (player = 0; player < players; player++) {
		cards[player] = (int**)malloc(ROW * sizeof(int*));
		empty_space[player] = (int**)malloc(ROW * sizeof(int*));		
		for (row = 0; row < ROW; row++) {
			cards[player][row] = (int*)malloc(COLUMN * sizeof(int));
			empty_space[player][row] = (int*)malloc(EMPTY_SPACE * sizeof(int));			
		}			
	}

	// clean up before the new game
	draw_cnt = 0;
	for (draw_index = 0; draw_index < MAX_DRAWN; draw_index++) {
		drawn_card[draw_index] = 0;
	}
								
	// store 3D arrays to pointer
	for (player = 0; player < players; player++) {		
		for (row = 0; row < ROW; row++) {

			// randomise the empty space					
			for (empty_index = 0; empty_index < EMPTY_SPACE; empty_index++) {															
				empty_space[player][row][empty_index] = rand() % 9;
					
				// check the repeated number
				while (empty_index == 1 && empty_space[player][row][empty_index] == empty_space[player][row][empty_index - 1]) {
					empty_space[player][row][empty_index] = rand() % 9;
				}
				while (empty_index == 2 && (empty_space[player][row][empty_index] == empty_space[player][row][empty_index - 1]
					|| empty_space[player][row][empty_index] == empty_space[player][row][empty_index - 2])) {
					empty_space[player][row][empty_index] = rand() % 9;
				}
				while (empty_index == 3 && (empty_space[player][row][empty_index] == empty_space[player][row][empty_index - 1]
					|| empty_space[player][row][empty_index] == empty_space[player][row][empty_index - 2]
					|| empty_space[player][row][empty_index] == empty_space[player][row][empty_index - 3])) {
					empty_space[player][row][empty_index] = rand() % 9;
				}					
			}

			// initialise 'range' as a default value
			range = 1;
			for (col = 0; col < COLUMN; col++) {				
				if (col == 9) {
					cards[player][row][col] = 0;
				}
				else {
					cards[player][row][col] = rand() % 10 + range;

					// check the repeated numbers
					while (row == 1 && cards[player][row][col] == cards[player][row - 1][col]) {
						cards[player][row][col] = rand() % 10 + range;
					}
					while (row == 2 && (cards[player][row][col] == cards[player][row - 1][col]
						|| cards[player][row][col] == cards[player][row - 2][col])) {
						cards[player][row][col] = rand() % 10 + range;
					}
				}

				// replace the random empty spaces
				for (empty_index = 0; empty_index < EMPTY_SPACE; empty_index++) {
					if (col == empty_space[player][row][empty_index]) {
						cards[player][row][col] = 99999;
					}
				}
				if (col != (COLUMN - 2)) {
					range += 10;
				}
			}
		}
	}

	// read and display arrays
	for (player = 0; player < players; player++) {
		printf("%dth player\n\n", player + 1);

		// display the form
		for (disp = 0; disp < COLUMN - 1; disp++) {
			if (disp == 0) {
				printf("       Col %d | ", disp + 1);
			}
			else if (disp == 8) {
				printf("Col %d |\n", disp + 1);
			}
			else {
				printf("Col %d | ", disp + 1);
			}
		}
		for (row = 0; row < ROW; row++) {
			printf("Row %d:  ", row + 1);		
			for (col = 0; col < COLUMN - 1; col++) {

				if (col == 0) {
					if (cards[player][row][col] == 99999) {
						printf("%2c   |  ", empty);
					}				
					else {
						printf("%2d   |  ", cards[player][row][col]);
					}
				}
				else if (col == 8) {
					if (cards[player][row][col] == 99999) {
						printf("%2c   |", empty);
					}
					else {
						printf("%2d   |", cards[player][row][col]);
					}
				}
				else {
					if (cards[player][row][col] == 99999) {
						printf("%2c   |  ", empty);
					}					
					else {
						printf("%2d   |  ", cards[player][row][col]);
					}
				}
			}
			printf("\n");
		}
		for (int s = 0; s < 78; s++) {
			printf("-");
		}
		printf("\n");
	}
}

void draw_cards(void) {

	// declare and initialise variables
	int draw, draw_find;
	srand(time(NULL));

	//for (int m = 0; m < 75; m++) { // test drawing cards n times	
				
	// draw and check the repeated cards
	draw = rand() % 90 + 1;
	if (draw_cnt != 0) {
		do {
			for (draw_index = 0; draw_index < draw_cnt; draw_index++) {
				if (draw == drawn_card[draw_index]) {
					draw = rand() % 90 + 1;
					draw_find = 1;
					break;
				}
				else {
					draw_find = 0;
				}
			}
		} while (draw_find == 1);
	}
	drawn_card[draw_cnt] = draw;
	draw_cnt++;
	printf("\n");
	for (int s = 0; s < 35; s++) {
		printf(" ");
	}
	printf("Drawn number is: %d and count is: %d\n", draw, draw_cnt);
	printf("All drawn numbers [");		
	for (draw_index = 0; draw_index < draw_cnt; draw_index++) {
		printf(" %d", drawn_card[draw_index]);
	}			
	printf(" ]\n");

	// update the matched drawn cards
	for (player = 0; player < players; player++) {		
		for (row = 0; row < ROW; row++) {				
			for (col = 0; col < COLUMN; col++) {

				// find and update the drawn numbers from array
				if (col != 9 && draw == cards[player][row][col]) {			
					cards[player][row][col] = 0;
				}		
			}							
		}
	}

	//} // test ends
	printf("\n\n");	
}

void save_game(void) {
	
	// declare and initialise variables
	FILE *save_file;
	save_file = fopen(file_name, "w");

	if (save_file == NULL) {
		printf("File cannot be processed! \n");
	}
	else {
		fprintf(save_file, "%d %d ", draw_cnt, players);
		for (draw_index = 0; draw_index < draw_cnt; draw_index++) {
			fprintf(save_file, "%d ", drawn_card[draw_index]);
		}
		for (player = 0; player < players; player++) {
			for (row = 0; row < ROW; row++) {
				for (col = 0; col < COLUMN - 1; col++) {
					fprintf(save_file, "%d ", cards[player][row][col]);
				}
			}
		}
		printf("Game saved\n");
		fclose(save_file);
		get_sub_menu();
	}
}

void load_game(void) {

	// free dynamic memory
	// *need to free 3pointers! ont only one
	/*free(drawn_card);
	free(cards);
	free(empty_space);
	drawn_card = NULL;
	cards = NULL;
	empty_space = NULL;*/


	// declare and initialise variables
	FILE *load_file;
	load_file = fopen(file_name, "r");

	if (load_file == NULL) {
		printf("File cannot be found! \n");
	}
	else {

		// read the drawn card count and number of players
		fscanf(load_file, "%d %d ", &draw_cnt, &players);

		// allocate pointers
		drawn_card = (int*)malloc(draw_cnt * sizeof(int));
		cards = (int***)malloc(players * sizeof(int**));
		/*drawn_card = realloc(drawn_card, draw_cnt * sizeof(int));
		cards = realloc(cards, players * sizeof(int**));*/
		//empty_space = (int***)malloc(players * sizeof(int**));
		for (player = 0; player < players; player++) {
			cards[player] = (int**)malloc(ROW * sizeof(int*));
			//cards[player] = realloc(cards[player], ROW * sizeof(int*));
			//empty_space[player] = (int**)malloc(ROW * sizeof(int*));
			for (row = 0; row < ROW; row++) {
				cards[player][row] = (int*)malloc(COLUMN * sizeof(int));
				//cards[player][row] = realloc(cards[player][row], COLUMN * sizeof(int));
				//empty_space[player][row] = (int*)malloc(EMPTY_SPACE * sizeof(int));
			}
		}

		// read the drawn cards
		for (draw_index = 0; draw_index < draw_cnt; draw_index++) {
			fscanf(load_file, "%d ", &drawn_card[draw_index]);
		}
		for (player = 0; player < players; player++) {
			for (row = 0; row < ROW; row++) {
				for (col = 0; col < COLUMN - 1; col++) {
					fscanf(load_file, "%d ", &cards[player][row][col]);
				}
			}
		}
		printf("Game loaded\n");
		fclose(load_file);
		get_sub_menu();
	}
}

void get_status(void) {

	// declare and initialise variables
	int count, cnt, fcnt, total_cnt;

	// read and display arrays
	for (player = 0; player < players; player++) {
		printf("%dth player\n\n", player + 1);
		fcnt = 0;
		total_cnt = 0;

		// display the form
		for (disp = 0; disp < COLUMN; disp++) {
			if (disp == 0) {
				printf("       Col %d | ", disp + 1);
			}
			else if (disp == 9) {
				printf("Col %d (count)\n", disp + 1);
			}
			else {
				printf("Col %d | ", disp + 1);
			}
		}
		for (row = 0; row < ROW; row++) {
			printf("Row %d:  ", row + 1);

			// set the default count number			
			cnt = 0;				
			for (col = 0; col < COLUMN; col++) {

				if (col == 0) {
					if (cards[player][row][col] == 99999) {
						printf("%2c   |  ", empty);
					}
					else if (cards[player][row][col] == 00000) {
						printf("%2c   |  ", checked);
					}
					else {
						printf("%2d   |  ", cards[player][row][col]);
					}
				}
				else if (col == 9) {
					for (col = 0; col < COLUMN - 1; col++) {
						if (cards[player][row][col] == 00000) {
							cnt++;
						}						
					}					
					
					// store the count number
					cards[player][row][col] = cnt;
					printf("cnt %d rm_cnt %d", cnt, 5 - cnt);					
				}
				else {
					if (cards[player][row][col] == 99999) {
						printf("%2c   |  ", empty);
					}
					else if (cards[player][row][col] == 00000) {
						printf("%2c   |  ", checked);
					}
					else {
						printf("%2d   |  ", cards[player][row][col]);
					}
				}				
			}

			printf("\n");
		}
		for (int s = 0; s < 93; s++) {
			printf("-");
		}
		printf("\n");

		// check the four corners		
		if (cards[player][0][0] == 0) {
			fcnt++;
		}
		if (cards[player][0][8] == 0) {
			fcnt++;
		}
		if (cards[player][2][0] == 0) {
			fcnt++;
		}
		if (cards[player][2][8] == 0) {
			fcnt++;
		}

		// display the winning requiements
		printf("---For the four corners---\n");
		if (cards[player][0][0] == 99999 || cards[player][0][8] == 99999 || cards[player][2][0] == 99999 || cards[player][2][8] == 99999) {
			printf("Cannot make the four corners\n");
		}
		else {
			printf("%d numbers need\n", 4 - fcnt);
		}
		printf("---For the line---\n");
		for (row = 0; row < ROW; row++) {
			if (cards[player][row][9] == 5) {
				printf("==LINE!==\n");		
			}
			else {
				printf("%dth row needs %d numbers\n", row + 1, 5 - cards[player][row][9]);
			}			
		}
		printf("---For the two lines---\n");
		printf("The first and second rows combination needs %d numbers\n", 10 - (cards[player][0][9] + cards[player][1][9]));
		printf("The first and third rows combination needs %d numbers\n", 10 - (cards[player][0][9] + cards[player][2][9]));
		printf("The second and third rows combination needs %d numbers\n", 10 - (cards[player][1][9] + cards[player][2][9]));
		printf("---For the full house---\n");
		printf("%d numbers need\n", 15 - (cards[player][0][9] + cards[player][1][9] + cards[player][2][9]));
		printf("\n");
	}
}