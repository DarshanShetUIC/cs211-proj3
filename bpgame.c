

// file:  bpgame.c


/** #include statements... **/


/** TYPEDEFS / STRUCTs HERE ***/


struct bpgame {


   // YOU DECIDE WHAT TO PUT IN HERE TO CAPTURE THE STATE OF
   //   A "RUN" OF THE GAME.....
	int rows;
	int cols;
	
	int score;
	
	BPGame* prev;
	BPGame* next;
	
	int** arr;

} BPGame;





/*** IMPLEMENTATION OF bp_XXXX FUNCTIONS HERE  ****/

BPGame * bp_create(int nrows, int ncols){
	if (nrows < 0 || nrows > 40 || ncols < 0 || ncols > 40){
		fprintf(stderr, "%s", "nrows or ncols out of bounds!!!");
		return NULL;
	}
	
}
