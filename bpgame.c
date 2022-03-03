

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
	
	BPGame* head;
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
	
	// Create board. This board is what gets changed all the time. Not added to stack.
	BPGame* b = (BPGame*) malloc(sizeof(BPGame));
	b->rows = nrows;
	b->cols = ncols;
	b->score = 0;
	b->head = NULL;
	b->prev = NULL;
	b->arr = (char**) malloc(b->rows * sizeof(char*));
	int i = 0;
	for (i; i < nrows; i++){
		b->arr[i] = (char*) malloc(b->cols * sizeof(char));
	}
	
	// Set random seed
	srand(time(0));
	
	// Populate board with random balloons
	i = 0;
	int j = 0;
	for (i; i < b->rows; i++){
		//printf("Row index: %d\n", i);
		for(j; j < b->cols; j++){
			//printf("Row column: %d\n", j);
			int rchar = (rand() % 4) + 1;
			if (rchar == 0){b->arr[i][j] = None;}
			if (rchar == 1){b->arr[i][j] = Red;}
			if (rchar == 2){b->arr[i][j] = Blue;}
			if (rchar == 3){b->arr[i][j] = Green;}
			if (rchar == 4){b->arr[i][j] = Yellow;}	
		}
		j = 0;
	}
	
	// Create BPGame state to put on stack at the very bottom, same state (original) as BPGame root state returned to bpop
	BPGame* orig = (BPGame*) malloc(sizeof(BPGame));
	orig->rows = b->rows;
	orig->cols = b->cols;
	orig->score = b->score;
	orig->head = NULL;
	orig->prev = NULL;
	orig->arr = (char**) malloc(orig->rows * sizeof(char*));
	i = 0;
	for (i; i < orig->rows; i++){
		orig->arr[i] = (char*) malloc(orig->cols * sizeof(char));
	}
	i = 0;
	j = 0;
	for (i; i < orig->rows; i++){
		for(j; j < orig->cols; j++){
			orig->arr[i][j] = b->arr[i][j];
		}
		j = 0;
	}
	b->head = orig;
	return b;
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
	curr->head = NULL;
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
	// Destroy stack with all contents
	while(b->head != NULL){
		BPGame* temp = b->head->prev;
		int i = 0;
		for (i; i < b->rows; i++){
			free(b->head->arr[i]);
		}
		free(b->head->arr);
		free(b->head);
		b->head = temp;
	}

	// Destroy game board state
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
	// Get balloon color
	int color = bp_get_balloon(b,r,c);
	// If single balloon in location with specific color, quit
	if (!can_pop_rc(b,r,c,color)){
		return 0;
	}
	
	// Create new node and add to stack
	BPGame* curr = (BPGame*) malloc(sizeof(BPGame));
	curr->rows = b->rows;
	curr->cols = b->cols;
	curr->score = b->score;
	curr->head = NULL;
	curr->prev = b->head;
	b->head = curr;
	curr->arr = (char**) malloc(curr->rows * sizeof(char*));
	
	// Finish new BPGame state by setting up game board	
	int i = 0;
	for (i; i < curr->rows; i++){
		curr->arr[i] = (char*) malloc(curr->cols * sizeof(char));
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
	
	// Go pop similar balloons in new state, change score as well
	int numPopped = r_pop(curr,r,c,color);
	curr->score = curr->score + numPopped * (numPopped - 1);
	
	// Reflect new changes to bpop game board and score
	b->score = curr->score;
	// Copy balloons from prev state
	i = 0;
	j = 0;
	for (i; i < curr->rows; i++){
		for(j; j < curr->cols; j++){
			b->arr[i][j] = curr->arr[i][j];
		}
		j = 0;
	}
	
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
	BPGame* prevState = b->head->prev;
	
	// forget recent move
	if (prevState == NULL){
		return 0;
	}
	int i = 0;
	for (i; i < b->rows; i++){
		free(b->head->arr[i]);
	}
	free(b->head->arr);
	free(b->head);
	
	// return to previous move
	b->head = prevState;
	i = 0;
	int j = 0;
	for (i; i < b->rows; i++){
		for(j; j < b->cols; j++){
			b->arr[i][j] = b->head->arr[i][j];
		}
		j = 0;
	}
	b->score = b->head->score;
	return 1;
}
