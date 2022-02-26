

// file:  bpgame.c


/** #include statements... **/
#include <stdio.h>
#include <stddef.h>

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
	if (nrows < 0 || nrows > 40 || ncols < 0 || ncols > 40){
		printf("nrows or ncols out of bounds!!!");
		return NULL;
	}
	return NULL;
}

BPGame * bp_create_from_mtx(char mtx[][MAX_COLS], int nrows, int ncols){
	return NULL;
}

void bp_destroy(BPGame * b){
	return;
}

void bp_display(BPGame * b){
	return;
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
	return 0;
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
