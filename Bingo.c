#include<stdio.h>
#include"bingo.h"

void menu_interface(void) {

	for (int s = 0; s < 54; s++) {
		printf("=");
	}
	printf("\n");
	printf("|  ****      ***     *   ***     ****        ****    |\n");
	printf("|  *   *      *      **   *     *           *    *   |\n");
	printf("|  ****       *      * *  *    *    ***    *      *  |\n");	
	printf("|  *    *     *      *  * *     *    *      *    *   |\n");	
	printf("|  *****     ***    ***   *      ****        ****    |\n");	
	for (int s = 0; s < 54; s++) {
		printf("=");
	}	
	printf("\n\n");
	get_start_main_menu();
}

void main(void) {

	menu_interface();

}