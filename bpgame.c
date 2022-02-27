

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
	// Print top border
	printf("\n+");
	int i = 0;
	int top_row_edge = 2 * b->cols + 1;
	for (i; i < top_row_edge; i++){
		printf("-");
	}
	printf("+\n");
	
	
	// print walls and characters
	i = 0;
	int j = 0;
	for (i; i < b->rows; i++){
		printf("| ");
		for (j; j < b->cols; j++){
			printf("%c ", b->arr[i][j]);
		}
		printf("|\n");
		j = 0;
	}
	
	// Print bottom border
	printf("+");
	i = 0;
	for (i; i < top_row_edge; i++){
		printf("-");
	}
	printf("+\n");	
}

int bp_pop(BPGame * b, int r, int c){
	return 0;
}

int bp_is_compact(BPGame * b){
	int i = 0;
	int j = 0;
	for (i; i < b->cols; i++){
		for (j; j < b->rows-1; j++){
			if (b->arr[j][i] == None && b->arr[j+1][i] != None){return 0;}
		}
		j = 0;
	}
	return 1;
}

void swap_places(BPGame * b, int row, int col){
	char swp = b->arr[row][col];
	b->arr[row][col] = b->arr[row+1][col];
	b->arr[row+1][col] = swp;
}

void bp_float_one_step(BPGame * b){
	int i = 0;
	int j = 0;
	for (i; i < b->cols; i++){
		for (j; j < b->rows-1; j++){
			if (b->arr[j][i] == None && b->arr[j+1][i] != None){swap_places(b, j, i);}
		}
		j = 0;
	}
}

int bp_score(BPGame * b){
	return b->score;
}

int bp_get_balloon(BPGame * b, int r, int c){
	return (int) b->arr[r][c];
}

int bp_can_pop(BPGame * b){
	int i = 0;
	int j = 0;
	for (i; i < b->rows; i++){
		for (j; j < b->cols; j++){
			// Check balloon below
			if (i+1 < b->rows){if (b->arr[i+1][j] != None || b->arr[i][j] != None){if (b->arr[i][j] == b->arr[i+1][j]){return 1;}}}
			// Check balloon above
			if (i-1 >= 0){if (b->arr[i-1][j] != None || b->arr[i][j] != None){if (b->arr[i][j] == b->arr[i-1][j]){return 1;}}}
			// Check balloon on the right
			if (j+1 < b->cols){if (b->arr[i][j+1] != None || b->arr[i][j] != None){if (b->arr[i][j] == b->arr[i][j+1]){return 1;}}}
			// Check balloon on the left
			if(j-1 >= 0){if (b->arr[i][j-1] != None || b->arr[i][j] != None){if (b->arr[i][j] == b->arr[i][j-1]){return 1;}}}
		}
		j = 0;
	}
	return 0;
}

int bp_undo(BPGame * b){
	BPGame* prevState = b->prev;
	if (prevState == NULL){return 0;}
	int i = 0;
	for (i; i < b->rows; i++){
		free(b->arr[i]);
	}
	free(b->arr);
	free(b);
	b = prevState;
	return 1;
}


int main(){
	printf("\n");
	int r = 4;
	int c = 5;
	BPGame* board = bp_create(r,c);
	bp_display(board);
	bp_float_one_step(board);
	bp_display(board);
	//printf("\n%c\n", board->arr[2][2]);
	//printf("\nCan pop?: %d\n", bp_can_pop(board));
	bp_destroy(board);
	printf("\n");
	return 0;
}

