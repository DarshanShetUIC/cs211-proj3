

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
	curr->score = 0;
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
			int rchar = (rand() % 4) + 1;
			if (rchar == 0){curr->arr[i][j] = None;}
			if (rchar == 1){curr->arr[i][j] = Red;}
			if (rchar == 2){curr->arr[i][j] = Blue;}
			if (rchar == 3){curr->arr[i][j] = Green;}
			if (rchar == 4){curr->arr[i][j] = Yellow;}	
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
	curr->score = 0;
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
			if (mtx[i][j] == None || mtx[i][j] == None || mtx[i][j] == None || mtx[i][j] == None || mtx[i][j] == None){
				curr->arr[i][j] = mtx[i][j];
			}
			else{
				printf("Not valid character!!!\n");
				return NULL;
			}
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

int r_pop(BPGame* b, int r, int c, int color){
	//printf("\nPopping balloon at %d %d\n", r, c);
	b->arr[r][c] = None;
	int numPopped = 1;
	if(r-1 >= 0){
		if(color == b->arr[r-1][c]){
			numPopped = numPopped + r_pop(b,r-1,c,color);
		}
	}
	if(r+1 < b->rows){
		if(color == b->arr[r+1][c]){
			numPopped = numPopped + r_pop(b,r+1,c,color);
		}
	}
	if(c-1 >= 0){
		if(color == b->arr[r][c-1]){
			numPopped = numPopped + r_pop(b,r,c-1,color);
		}
	}
	if(c+1 < b->cols){
		if(color == b->arr[r][c+1]){
			numPopped = numPopped + r_pop(b,r,c+1,color);
		}
	}
	return numPopped;
}

int can_pop_rc(BPGame* b, int r, int c, int color){
	int hasNeighbors = 0;
	if(r-1 >= 0){
		if(color == b->arr[r-1][c]){
			hasNeighbors++;
		}
	}
	if(r+1 < b->rows){
		if(color == b->arr[r+1][c]){
			hasNeighbors++;
		}
	}
	if(c-1 >= 0){
		if(color == b->arr[r][c-1]){
			hasNeighbors++;
		}
	}
	if(c+1 < b->cols){
		if(color == b->arr[r][c+1]){
			hasNeighbors++;
		}
	}
	if(hasNeighbors){
		return 1;
	}
	else{
		return 0;
	}
}

int bp_pop(BPGame * b, int r, int c){
	//printf("\nAddress of b: %p\n", b);
	// Get balloon color
	int color = bp_get_balloon(b,r,c);
	// If single balloon in location with specific color, quit
	if (!can_pop_rc(b,r,c,color)){
		return 0;
	}
	
	// Create new state
	BPGame* curr = (BPGame*) malloc(sizeof(BPGame));
	//printf("\nAddress of curr: %p\n", curr);
	curr->rows = b->rows;
	curr->cols = b->cols;
	curr->score = b->score;
	curr->next = NULL;
	curr->prev = b;
	curr->arr = (char**) malloc(b->rows * sizeof(char*));
	int i = 0;
	for (i; i < b->rows; i++){
		curr->arr[i] = (char*) malloc(b->cols * sizeof(char));
	}
	// Copy balloons from prev state
	i = 0;
	int j = 0;
	for (i; i < curr->rows; i++){
		for(j; j < curr->cols; j++){
			curr->arr[i][j] = b->arr[i][j];
		}
		j = 0;
	}
	
	// Go pop similar balloons in new state
	int numPopped = r_pop(curr,r,c,color);
	curr->score = curr->score + numPopped * (numPopped - 1);
	
	// Remember curr node in b, Set b to new state
	b->next = curr;
	b = curr;
	//printf("\nAddress of b: %p\n", b);
	return numPopped;
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
	// remember previous move
	BPGame* prevState = b->prev;
	// forget current move
	if (prevState == NULL){return 0;}
	int i = 0;
	for (i; i < b->rows; i++){
		free(b->arr[i]);
	}
	free(b->arr);
	free(b);
	// return to previous move
	b = prevState;
	return 1;
}
