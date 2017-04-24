#include<stdio.h>
#include"bingo.h"

int get_choice(void) {

	// define variables
	int choice;
	
	printf("Enter a number: ");
	scanf("%d", &choice);
	printf("\n");

	// loop for the validation; 1. only positive number, 2. only integer type
	while (choice < 0) {		
		printf("\n!Invalid input\n");
		printf("Please enter a positive number: ");
		scanf("%d", &choice);
		printf("\n");
	}

	return choice;
}

int *get_manager_menu(void) {

	// define variables
	int manager_choice;

	printf("How many players are playing?\n");			
	manager_choice = get_choice();

	// loop for the validation
	while (manager_choice == 0) {
		printf("\n!Invalid input\n");
		printf("Please enter a number more than 0: ");
		scanf("%d", &manager_choice);
	}

	return manager_choice;
}

void get_main_menu(void) {

	// define variables
	int player_choice;	
	
	printf("1 - New Game\n");
	printf("2 - Continue\n");
	printf("3 - Exit\n");
	player_choice = get_choice();

	// loop for the validation
	while (player_choice < 1 || player_choice > 3) {
		printf("\n!Invalid input\n");
		printf("Please enter a number between 1 and 3: ");
		scanf("%d", &player_choice);
	}

	switch (player_choice)
	{
	case 1:
		generate_cards();		
		get_sub_menu();
		break;
	case 2:
		load_game();		
		break;
	case 3:
		printf("Bye Bye\n");
		break;
	default:
		printf("unexpected error!! from main menu\n");
		printf("Fix me!!!\n");
		break;
	}
}

void get_sub_menu(void) {

	// define variables
	int player_choice;

	printf("1 - Draw the next card\n");
	printf("2 - Save the game\n");
	printf("3 - Display the current game status\n");
	printf("4 - Exit the game\n");
	player_choice = get_choice();

	// loop for the validation
	while (player_choice < 1 || player_choice > 4) {
		printf("\n!Invalid input\n");
		printf("Please enter a number between 1 and 4: ");
		scanf("%d", &player_choice);
	}

	switch (player_choice)
	{
	case 1:
		draw_cards();
		get_sub_menu();
		break;
	case 2:
		save_game();		
		break;
	case 3:
		get_status();		
		get_sub_menu();
		break;
	case 4:
		get_exit_menu();
		break;
	default:
		printf("unexpected error!! from sub menu\n");
		printf("Fix me!!!\n");
		break;
	}
}

//void get_exit_menu(void) {
//
//	// define variables
//	int player_choice;
//
//	printf("*Warning* this option will terminate the current game\n");
//	printf("1 - Creat a new game\n");
//	printf("2 - Open the previous game\n");
//	printf("3 - Exit\n");	
//	player_choice = get_choice();
//
//	// loop for the validation
//	while (player_choice < 1 || player_choice > 3) {
//		printf("\n!Invalid input\n");
//		printf("Please enter a number between 1 and 3: ");
//		scanf("%d", &player_choice);
//	}
//	
//}