#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (2048)

struct elt {
    struct elt *next;
    char value;
    int pos;
};

/*
 * We could make a struct for this,
 * but it would have only one component,
 * so this is quicker.
 */
typedef struct elt *Elt;

#define STACK_EMPTY (0)

void
destroyOutput(Elt *rows, int length){
	int i;
	Elt nextRow;
	for(i = 0; i < length; i++){
		Elt currRow = rows[i];

		while(currRow->next != 0){
			nextRow = currRow->next;
			free(currRow);
			currRow = nextRow;
		}
	}
	free(rows);
}

void
printOutput(Elt *rows, int length){
	int i;
	int pos;
	for(i = 0; i < length; i++){
		Elt currRow = rows[i];
		pos = 0;

		while(currRow->next != 0){
			while(pos < (currRow->pos - 1)){
				putchar(' ');
				pos++;
			}
			putchar(currRow->value);
			currRow = currRow->next;
			pos++;
		}
		putchar('\n');
	}
}

int
main(int argc, char **argv) {
  char filename[BUFFER_SIZE];
  FILE *f;

  Elt *rows;

  int col;
	int row;
	int size = 1;
	int index = 0;
	int maxIndex = 0;
	int pos;

	rows = (Elt *) malloc(sizeof(Elt) * size);
	rows[index] = malloc(sizeof(struct elt));
	Elt currElt = rows[index];
	currElt->value = 0;
  currElt->pos = 0;
 	currElt->next = 0;

  while(scanf("%d %d %s", &row, &col, filename) == 3) {
    f = fopen(filename, "r");

    if(f == 0) {
      perror(filename);
      exit(2);
    }

  	if(row <= maxIndex){
  		index = row;
  	} else {
  		if(row > maxIndex){
  			index = maxIndex;
  			free(rows[index]);
  			rows[index] = malloc(sizeof(struct elt));
  			currElt = rows[index];
  			while(index < row){
  				currElt->pos = 0;
				  currElt->next = 0;
				  index++;
				  if(size <= index){
	    			size *= 2;
	    			rows = realloc(rows, sizeof(Elt) * size);
	    		}
	    		rows[index] = malloc(sizeof(struct elt));
	    		currElt = rows[index];
  			}
  		} else {
  			for(int i = 0; i < row; i++){
  				currElt->pos = 0;
  				currElt->next = 0;
  				index++;
  				if(size <= index){
      			size *= 2;
      			rows = realloc(rows, sizeof(Elt) * size);
      		}
	    		rows[index] = malloc(sizeof(struct elt));
	    		currElt = rows[index];
	    	}
  		}
    }

  	currElt = rows[index];
  	pos = col+1;
  	int c;

  	while((c = getc(f)) != EOF) {
  		if(index < maxIndex && maxIndex > 0){
    		if(c != ' '){
    			if(c != '\n'){
    				while(currElt->pos < pos){
							if(currElt->next != 0){
								currElt = currElt->next;
							} else {
								break;
							}
					  }
    				if(currElt->pos == pos){
    					if(currElt->next == 0){
    						currElt->next = (Elt) malloc(sizeof(struct elt));
    					}
    					currElt->value = c;
    					currElt = currElt->next;
    				} else {
    					if(currElt->pos < pos){
	    					struct elt *newElt;
		    				newElt = (Elt) malloc(sizeof(struct elt));

		    				currElt->value = c;
				    		currElt->pos = pos;
				    		currElt->next = newElt;
				    		currElt = newElt;
				    	} else {
					    	struct elt *newElt;
			    			newElt = (Elt) malloc(sizeof(struct elt));

			    			char oldVal = currElt->value;
			    			int oldPos = currElt->pos;
			    			Elt oldNext = currElt->next;

			    			currElt->value = c;
			    			currElt->pos = pos;
			    			currElt->next = newElt;

			    			newElt->value = oldVal;
			    			newElt->pos = oldPos;
			    			newElt->next = oldNext;

			    			currElt = newElt;
					    }
    				}
	    		} else {
	    			if(pos <= (currElt->pos+1)){
	    				while(currElt->next != 0){
	    					currElt = currElt->next;
	    				}
	    			} else {
	    				currElt->value = c;
	    				currElt->pos = pos;
	    				currElt->next = 0;
	    			}
	    			index++;
	    			pos = col;
	    			currElt = rows[index];
	    		}
    		}
    	} else {
    		if(c != ' '){
    			if(c != '\n'){
	    			struct elt *newElt;
	    			newElt = (Elt) malloc(sizeof(struct elt));

	    			currElt->value = c;
		    		currElt->pos = pos;
		    		currElt->next = newElt;
		    		currElt = newElt;
	    		} else {
	    			currElt->value = c;
	    			currElt->pos = pos;
	    			currElt->next = 0;
	    			index++;
	    			pos = col;
	    			if(size <= index){
		    			size *= 2;
		    			rows = realloc(rows, sizeof(Elt) * size);
		    		}
		    		rows[index] = malloc(sizeof(struct elt));
	    			currElt = rows[index];
	    		}
    		}
    	}
  		pos++;
  	}
  	if(maxIndex < index){
  		maxIndex = index;
  	}
  	index = 0;
  	fclose(f);
  }
  if(size > maxIndex){
  	rows = realloc(rows, sizeof(Elt) * maxIndex);
  }
  printOutput(rows, maxIndex);
  destroyOutput(rows, maxIndex);

	return 0;
}
