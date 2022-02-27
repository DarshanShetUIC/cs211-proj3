

// file:  bpgame.c


/** #include statements... **/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <ctype.h>

#include "bpgame.h"

/** TYPEDEFS / STRUCTs HERE ***/


typedef struct bpgame {


   // YOU DECIDE WHAT TO PUT IN HERE TO CAPTURE THE STATE OF
   //   A "RUN" OF THE GAME.....
	int rows;
	int cols;
	
	int score;
	
	BPGame* next;
	BPGame* prev;
	
	char** arr;

} BPGame;





/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/

BPGame * bp_create(int nrows, int ncols){
	// Check bounds
	if (nrows < 0 || nrows > 40 || ncols < 0 || ncols > 40){
		printf("nrows or ncols out of bounds!!!");
		return NULL;
	}
	
	// Create board
	BPGame* curr = (BPGame*) malloc(sizeof(BPGame));
	curr->rows = nrows;
	curr->cols = ncols;
	curr->next = NULL;
	curr->prev = NULL;
	curr->arr = (char**) malloc(nrows * sizeof(char*));
	int i = 0;
	for (i; i < nrows; i++){
		curr->arr[i] = (char*) malloc(ncols * sizeof(char));
	}
	
	// Set random seed
	srand(time(0));
	
	// Populate board with random balloons
	i = 0;
	int j = 0;
	for (i; i < nrows; i++){
		//printf("Row index: %d\n", i);
		for(j; j < ncols; j++){
			//printf("Row column: %d\n", j);
			int rchar = rand() % 5;
			if (rchar == 0){curr->arr[i][j] = None;}
			else if (rchar == 1){curr->arr[i][j] = Red;}
			else if (rchar == 2){curr->arr[i][j] = Blue;}
			else if (rchar == 3){curr->arr[i][j] = Green;}
			else if (rchar == 4){curr->arr[i][j] = Yellow;}	
		}
		j = 0;
	}
	return curr;
}

BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){
	// Check bounds
	if (nrows < 0 || nrows > 40 || ncols < 0 || ncols > 40){
		printf("nrows or ncols out of bounds!!!");
		return NULL;
	}
	
	// Create board
	BPGame* curr = (BPGame*) malloc(sizeof(BPGame));
	curr->rows = nrows;
	curr->cols = ncols;
	curr->next = NULL;
	curr->prev = NULL;
	curr->arr = (char**) malloc(nrows * sizeof(char*));
	int i = 0;
	for (i; i < nrows; i++){
		curr->arr[i] = (char*) malloc(ncols * sizeof(char));
	}
	
	// Set random seed
	srand(time(0));
	
	// Populate board with balloons from mtx
	i = 0;
	int j = 0;
	for (i; i < nrows; i++){
		//printf("Row index: %d\n", i);
		for(j; j < ncols; j++){
			//printf("Row column: %d\n", j);
			curr->arr[i][j] = mtx[i][j];
		}
		j = 0;
	}
	return curr;
}

void bp_destroy(BPGame * b){
	int i = 0;
	for (i; i < b->rows; i++){
		free(b->arr[i]);
	}
	free(b->arr);
	free(b);
}

void bp_display(BPGame * b){
	
}

int bp_pop(BPGame * b, int r, int c){
	return 0;
}

int bp_is_compact(BPGame * b){
	return 0;
}

void bp_float_one_step(BPGame * b){
	return;
}

int bp_score(BPGame * b){
	return b->score;
}

int bp_get_balloon(BPGame * b, int r, int c){
	return 0;
}

int bp_can_pop(BPGame * b){
	return 0;
}

int bp_undo(BPGame * b){
	return 0;
}
/*
int main(){
	printf("\nHi!\n");
	
	printf("Bye!\n");
	return 0;
}
*/
